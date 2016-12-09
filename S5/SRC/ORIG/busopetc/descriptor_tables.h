#include "isr.h"
#include "../prereq/string.h"

void init_descriptor_tables();

// kernel stack mod
void set_kernel_stack(u32int stack);

// Keeps alignment given one GDT entry
struct gdt_entry_struct
{
    u16int limit_low;
    u16int base_low;
    u8int  base_middle;
    u8int  access;              // Ring level, geme dat 3
    u8int  granularity;
    u8int  base_high;
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

// GDPT pointer for lgdt instruction.
struct gdt_ptr_struct
{
    u16int limit;               // selector limits
    u32int base;                // first gdt_entry_t struct
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;

// interrupt gate struct.
struct idt_entry_struct
{
    u16int base_lo;             // interrupt jump address
    u16int sel;                 // Kernel segment selector
    u8int  always0;             // 000000000000000000000000000
    u8int  flags;               // FLAGS AND FLAGS AND FLAGS
    u16int base_hi;             // Other stuff to jump too
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// Interrupt handlers pointer NOTE: useful for lidt
struct idt_ptr_struct
{
    u16int limit;
    u32int base;                // first element idt_entry_
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;

// Task State Segment
struct tss_entry_struct
{
    u32int prev_tss;   // The previous TSS NOTE: hardware management -> linked list
    u32int esp0;       // Stack pointer for kernel mode
    u32int ss0;        // S. Seg. for ...
    u32int esp1;       // no-thing
    u32int ss1;
    u32int esp2;  
    u32int ss2;   
    u32int cr3;   
    u32int eip;   
    u32int eflags;
    u32int eax;
    u32int ecx;
    u32int edx;
    u32int ebx;
    u32int esp;
    u32int ebp;
    u32int esi;
    u32int edi;
    u32int es;         // ES - kernel mode.
    u32int cs;         // \/
    u32int ss;         
    u32int ds;         
    u32int fs;         
    u32int gs;         
    u32int ldt;        // no-thing
    u16int trap;
    u16int iomap_base;

} __attribute__((packed));

typedef struct tss_entry_struct tss_entry_t;


// ISR goodies
extern "C" void isr0 ();
extern "C" void isr1 ();
extern "C" void isr2 ();
extern "C" void isr3 ();
extern "C" void isr4 ();
extern "C" void isr5 ();
extern "C" void isr6 ();
extern "C" void isr7 ();
extern "C" void isr8 ();
extern "C" void isr9 ();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
extern "C" void irq0 ();
extern "C" void irq1 ();
extern "C" void irq2 ();
extern "C" void irq3 ();
extern "C" void irq4 ();
extern "C" void irq5 ();
extern "C" void irq6 ();
extern "C" void irq7 ();
extern "C" void irq8 ();
extern "C" void irq9 ();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();
extern "C" void isr128();