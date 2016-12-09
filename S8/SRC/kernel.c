//Many thanks to OSDev and James Malloy!

#include "prereq/tdef.h"
#include "screenout.h"
#include "busopetc/descriptor_tables.h"
#include "busopetc/timer.h"
#include "memall/page.h"

//DEBUG
void kill_kernel();

int kernel_main()
{
	terminal_init();
	kout("KERNEL LEVEL\nBUILD:PSF022B\n================================================================================\n\n");
	
	kout("Setting GDT & Initializing IDT... ");
	init_descriptor_tables();
	kout("Finished\n");
	
	kout("Timer OFF - Functioning\n");
	
	kout("Initializing Paging... ");
	initialise_paging();
	kout("Finished");
	
	kout("\n<<<S-INIT GO>>>");
	
	kout("\n\nTesting Alloc & Free:");
	
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
	
	kout("\nFreeing... ");
	koint(v1);
	kochr('@');
	kohex(sp1);
	kout(" + ");
	koint(v1);
	kochr('@');
	kohex(sp2);
	kfree(sp1);
	kfree(sp2);
	
	kout("\n\nAllocating ");
	koint(v1*4);
	kout("... ");
	u32int sp3 = kmalloc(v1*4);
	koint(v1*4);
	kochr('@');
	kohex(sp3);
	
	kout("\nFreeing... ");
	koint(v1*4);
	kochr('@');
	kohex(sp3);
	
	return 25;
}