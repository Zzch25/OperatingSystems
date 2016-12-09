[BITS 32]

global start

PAGE_ALIGN equ 1<<0
MEMINF equ 1<<1
MAGIC equ 0x1BADB002
FLAGS equ PAGE_ALIGN | MEMINF
CHKSUM equ -(MAGIC + FLAGS)

mboot:
    dd  MAGIC
    dd  FLAGS
    dd  CHKSUM

section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:
		
extern kernel

section .text	
start:
	mov esp, stack_top
    ;get multiboot info
    push esp
    push ebx

    cli
    call kernel
    jmp $