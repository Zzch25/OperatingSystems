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
	kout("Finished\n");
	
	kout("\nPAGING TEST:\n");
	u32int *testp = (u32int*)0x25000000;
	kout("Sent address...\n");
    u32int PF = *testp;
	kout("Attempt access...\n");
	
	return 25;
}