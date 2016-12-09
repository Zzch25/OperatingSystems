//Many thanks to OSDev and James Malloy!

#include "prereq/tdef.h"
#include "screenout.h"
#include "busopetc/descriptor_tables.h"
#include "busopetc/timer.h"
#include "memall/page.h"
#include "filesys/initrd.h"
#include "filesys/fs.h"
#include "multiboot.h"
#include "memall/panic.h"

/*
typedef struct multiboot_memory_map {
	unsigned int size;
	unsigned int base_addr_low,base_addr_high;
// You can also use: unsigned long long int base_addr; if supported.
	unsigned int length_low,length_high;
// You can also use: unsigned long long int length; if supported.
	unsigned int type;
} multiboot_memory_map_t;
*/

extern u32int placement_address;

int kernel_main(struct multiboot *mboot_ptr)
{
	fs_node_t *fs_root = 0; 
	
	terminal_init();
	
	kout("KERNEL LEVEL\nBUILD:PSF022D\n===============================================================================\n\n");
	
	kout("Setting GDT & Initializing IDT... ");
	init_descriptor_tables();
	kout("Finished\n");
	
	/*
	multiboot_memory_map_t* mmap = mboot_ptr->mmap_addr;
	while(mmap < mboot_ptr->mmap_addr + mboot_ptr->mmap_length)
	{
		mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
		kohex(mmap->base_addr_low);
	}
	*/
	
	kout("Timer OFF - Functioning\n");
	
	kout("\nFinding Ram Disk... ");
	ASSERT(mboot_ptr->mods_count > 0);
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
    placement_address = initrd_end;
	kout("Found\n");
	kout(">");
	kohex(initrd_location);
	kout("\n<");
	kohex(initrd_end);
	kout("\n\n");
	
	kout("Initializing Paging... \n");
	initialise_paging();
	kout("Finished - Alloc Ready\n");
	
	kout("Initializing Ram Disk... ");
    fs_root = initialise_initrd(initrd_location);
	kout("Finished\n");

	kout("\n<<<FST>>>\n");
	readelems(fs_root);
	
	return 25;
}