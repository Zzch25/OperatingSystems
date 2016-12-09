//service routines and interrupt request handlers.

#include "isr.h"
//monitor removed.. handle this !!!!!!!!!!!!!!!!!!!!!

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

// Called on interrupt
extern "C"
void isr_handler(registers_t regs)
{
    // Sign extension 8->32
    u8int int_no = regs.int_no & 0xFF;
    if (interrupt_handlers[int_no] != 0)
    {
        isr_t handler = interrupt_handlers[int_no];
        handler(&regs);
    }
    else
    {
        //monitor_write("unhandled interrupt: ");
        //monitor_write_hex(int_no);
        //monitor_put('\n');
        //for(;;);
    }
}

// Called on interrupt
extern "C"
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
        handler(&regs);
    }

}
