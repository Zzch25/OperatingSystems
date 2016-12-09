#include "sysdef/multiboot.h"
#include "sysdef/descriptor_tables.h"
#include "sysdef/timer.h"
#include "sysdef/paging.h"
#include "sysdef/initrd.h"
#include "sysdef/fs.h"
#include "sysdef/task.h"
#include "sysdef/syscall.h"
#include "sysdef/pbuff.h"
#include "sysdef/readrd.h"

extern u32int placement_address;
u32int initial_esp;

int kernel(struct multiboot *mboot_ptr, u32int initial_stack)
{
	terminal_init();
	
    initial_esp = initial_stack;
    init_descriptor_tables();
	
	kout("Update interrupt handling with per interrupt disabling\n");
	
    //asm volatile("sti");
    init_timer(50);

    ASSERT(mboot_ptr->mods_count > 0);
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
    placement_address = initrd_end;

    init_paging();

    init_tasking();
	/*
    fs_root = init_initrd(initrd_location);

	int ret = fork();

	kout("\n>>Process ");
	koint(getpid());
	kout(" Obtained Timeslice<<\n\n");
    
	if(getpid() == 1)
	{
		kout("Parent Reading Ramdisk...\n\n");
		asm volatile("cli");
		readelems(fs_root);
		asm volatile("sti");
		
		switch_task();
		
		kout(">>Process 1 Obtained Timeslice<<\n\n");
		kout("Process 1 Reaching Ring 3...\n");
		init_syscalls();
		switch_to_user_mode();
		syscall_kout("25! A Tale of User Mode\n");
	}
	else
	{
		kout("Child Process Testing Memory");
		
		u32int v1 = 25;
		
		kout("\n\nAllocating 50... ");
		u32int sp1 = kmalloc(v1);
		u32int sp2 = kmalloc(v1);
		koint(v1);
		kochr('@');
		kohex(sp1);
		kout(" + ");
		koint(v1);
		kochr('@');
		kohex(sp2);
		
		kout("\nFreeing...");
		koint(v1);
		kochr('@');
		kohex(sp1);
		kout(" + ");
		koint(v1);
		kochr('@');
		kohex(sp2);
		kfree(sp1);
		kfree(sp2);
		
		kout("\nDone\n\n");
	}
	*/
    return 0;
}
