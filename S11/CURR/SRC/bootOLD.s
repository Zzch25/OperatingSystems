[BITS 32]

global mboot
global start

PAGE_ALIGN equ 1<<0
MEMINF equ 1<<1
MAGIC equ 0x1BADB002
FLAGS equ PAGE_ALIGN | MEMINF
CHKSUM equ -(MAGIC + FLAGS)

extern code
extern bss
extern end                    

mboot:
    dd  MAGIC
    dd  FLAGS
    dd  CHKSUM
    
    dd  mboot
		dd  code ;.text
		dd  bss ;.data
		dd  end                     
		dd  start ;eip

extern kernel
	
start:
    ;get multiboot info
    push esp
    push ebx

    cli
    call kernel
    jmp $