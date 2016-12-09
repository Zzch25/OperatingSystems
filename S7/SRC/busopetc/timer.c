#include "timer.h"
#include "isr.h"
#include "../screenout.h"

u32int cycle = 0;

static void timer_callback(registers_t regs)
{
    cycle++;
    kout("C");
    koint(cycle);
	kout(" @");
	kohex(regs.int_no);
    kochr('\n');
}

void init_timer(u32int frequency)
{
    //register timer call
    register_interrupt_handler(IRQ0, &timer_callback);

    // 16 bit to PIT
    u32int divisor = 1193180 / frequency;

    // push command
    outb(0x43, 0x36);

    // Send bitwise therefore upper lower
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // push frequency
    outb(0x40, l);
    outb(0x40, h);
}
