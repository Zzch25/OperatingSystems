#include "page.h"
#include "kheap.h"

page_directory_t *kernel_directory=0;
page_directory_t *current_directory=0;

//bitset
u32int *frames;
u32int nframes;

//in halloc.c
extern u32int placement_address;
extern heap_t *kheap;
extern u32int read_eip();
extern u32int eip;

//bitset macros
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

//set bit->frames bitset
static void set_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

static void clear_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

static u32int test_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

static u32int first_frame()
{
    u32int i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++) //fails at 128
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            for (j = 0; j < 32; j++)
            {
                u32int toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                    return i*4*8+j;
            }
        }
    }
	//PANIC("Incorrect frame size"); // really for debugging
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable)
{	
    if(page->frame == 0)
    {
        u32int idx = first_frame();
        if (idx == (u32int)-1)
            PANIC("No frames free");
        set_frame(idx*0x1000); //CHEME CHEME CHEME CHEME
        page->present = 1;
        page->rw = (is_writeable)?1:0;
        page->user = (is_kernel)?0:1;
        page->frame = idx;
    }
}

void free_frame(page_t *page)
{
    u32int frame;
    if (frame=page->frame)
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void initialise_paging()
{
    //16MB per 1 - F *16 physical memory - the issue
    u32int mem_end_page = 0x1000000; //FIX ONE
	u32int xem;
	int i = 0;
	
    nframes = mem_end_page / 0x1000;
    frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes));
    memset(frames, 0, INDEX_FROM_BIT(nframes));
	
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    memset(kernel_directory, 0, sizeof(page_directory_t));
    current_directory = kernel_directory;
	
	//map pages in kernel heap area
    for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000)
        get_page(i, 1, kernel_directory);

	//RIGFIX ============================================
	
    //phys->virt
    for(i=0; i<placement_address+0x1000; i+=0x1000)
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
	/*
	xem = placement_address;
	for(i=initrd_s; i<initrd_e+0x1000; i+=0x1000)
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
	placement_address = xem;
	*/
	//RIGFIX ============================================
	
	//Allocate previously mapped pages
    for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000)
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
		
    //handler
    register_interrupt_handler(14, page_fault);

    //paging setup
    switch_page_directory(kernel_directory);
	
	//Kheap init - THE PROBLEM
    kheap = create_heap(KHEAP_START, KHEAP_START+KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    asm volatile("mov %0, %%cr3":: "r"(&dir->tablesPhysical));
    u32int cr0;
    asm volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; //paging
    asm volatile("mov %0, %%cr0":: "r"(cr0));
}

page_t *get_page(u32int address, int make, page_directory_t *dir)
{
    address /= 0x1000;
    //page table of
    u32int table_idx = address / 1024;

    if (dir->tables[table_idx]) //already assigned
        return &dir->tables[table_idx]->pages[address%1024];
    else if(make)
	{
        u32int tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        memset(dir->tables[table_idx], 0, 0x1000); // PAGES[ADDRESS] ADDED
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
	}
    return 0;
}


void page_fault(registers_t regs)
{
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    u32int faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    int present   = !(regs.err_code & 0x1); // Page not present
    int rw = regs.err_code & 0x2;           // Write operation?
    int us = regs.err_code & 0x4;           // Processor user-mode?
    int reserved = regs.err_code & 0x8;     // Overwritten CPU bits of page entry?
    int id = regs.err_code & 0x10;          // By instruction fetch?

    // Output an error message.
    kout("\nPF - ");
    if (present) {kout("WRAT ");}
    if (rw) {kout("RO @");}
    if (us) {kout("UM @");}
    if (reserved) {kout("RSRV @");}
    kohex(faulting_address);
    kochr('\n');
	kout("EIP: ");
	kohex(eip);
	kochr('\n');
    PANIC("(PF)");
}
