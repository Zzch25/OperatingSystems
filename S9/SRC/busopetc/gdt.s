global gdt_flush

gdt_flush:
    mov eax, [esp+4]  ; Get GDT pointer
    lgdt [eax]        ; Load it

    mov ax, 0x10      ; 0x10 GDT offset-> DS
    mov ds, ax        ; Load DS selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush   ; 0x08 Cs LARGE offset
.flush:
    ret

global idt_flush
	
idt_flush:
    mov eax, [esp+4]  ; Get IDT pointer as param
    lidt [eax]        ; Load it
    ret