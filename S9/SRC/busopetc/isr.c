//service routines and interrupt request handlers.

#include "../prereq/mem/memm.h"
#include "../prereq/str/string.h"
#include "../prereq/tdef.h"
#include "isr.h"
#include "../screenout.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

// Called on interrupt 
void isr_handler(registers_t regs)
{	
	if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
    else
    {
        kout("Interrupt: ");
		kohex(regs.int_no);
		kochr('\n');
    }
}

// Called on interrupt
void irq_handler(registers_t regs)
{
    // End of interrupt -> PICs
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Reset signal -> master
    outb(0x20, 0x20);
	
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}
