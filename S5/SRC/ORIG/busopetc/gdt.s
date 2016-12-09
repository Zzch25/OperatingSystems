global gdt_flush,idt_flush,tss_flush

gdt_flush:
    mov eax, [esp+4]  ; Get GDT pointer
    lgdt [eax]        ; Load it

    mov ax, 0x10      ; 0x10 GDT offset-> DS
    mov ds, ax        ; Load DS selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 Cs offset, O_o
.flush:
    ret

idt_flush:
    mov eax, [esp+4]  ; Get IDT pointer as param
    lidt [eax]        ; Load it
    ret

tss_flush:
 
 mov ax, 0x2B      ; Load TSS index
                      ; Index 0x28 -> 5th selector & 8 bytes
                      ; bottom bits 0x2B
                      ; ring 3
    ltr ax            ; 0x2B -> TS register.
    ret

