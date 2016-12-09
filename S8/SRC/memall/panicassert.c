#include "panic.h"

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    //Assertion failure
    asm volatile("cli");

    kout("ASS. FAILURE.. ;): ");
    kout(desc);
    kout(" @");
    kout(file);
    kout(":");
    koint(line);
    kout("\n");
    for(;;);
}