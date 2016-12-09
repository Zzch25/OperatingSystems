#include "../sysdef/syscall.h"
#include "../sysdef/isr.h"
#include "../sysdef/pbuff.h"

static void syscall_handler(registers_t *regs);

DEFN_SYSCALL1(kout, 0, const char*);
DEFN_SYSCALL1(kohex, 1, const char*);
DEFN_SYSCALL1(koint, 2, const char*);

static void *syscalls[3] =
{
    &kout,
    &kohex,
    &koint,
};
u32int num_syscalls = 3;

void init_syscalls()
{
    register_interrupt_handler (0x80, &syscall_handler);
}

void syscall_handler(registers_t *regs)
{
    if (regs->eax >= num_syscalls)
        return;

    void *location = syscalls[regs->eax];

    int ret;
    asm volatile (" \
      push %1; \
      push %2; \
      push %3; \
      push %4; \
      push %5; \
      call *%6; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
    " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
    regs->eax = ret;
}
