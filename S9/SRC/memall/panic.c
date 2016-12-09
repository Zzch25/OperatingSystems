#include "panic.h"

extern void panic(const char *message, const char *file, u32int line)
{
    //:(
    asm volatile("cli");

    kout("FAILURE: ");
    kout(message);
    kout(" @");
    kout(file);
    kout(":");
    koint(line);
    kout("\n");
    for(;;);
}
