//Many thanks to OSDev and James Malloy!

#include "screenout.h"
#include "busopetc/descriptor_tables.h"
#include "busopetc/timer.h"

//DEBUG
extern "C" void kill_kernel();

extern "C" 
void kernel_main()
{
	terminal_init();
	kout("KERNEL LEVEL\nBUILD:PSF022B\n================================================================================\n");
	
	kout("Testing Interrupts (Keyboards Coming Soon!)...");
	
	kout("\n\nSetting GDT & Initializing IDT...\n");
	init_descriptor_tables();
	
	kout("Testing Special Prints...\nInt: ");
	u32int test = 3025;
	koint(test);
	kout("\nHex: ");
	kohex(test);
	
	kout("\n\nTesting int $0x1...\n");
	asm volatile ("int $0x1");
	
	kout("\nTesting int $0x2...\n");
	asm volatile ("int $0x2");
	
	kout("\nTesting Via PIT Timer - Initializing Timer\n");
	asm volatile("sti");
	init_timer(50);
}

extern "C" void __cxa_pure_virtual()
{
    kout("ERROR: COULD NOT MAKE PVF");
}