[BITS 32]

; Declare constants used for creating a multiboot header.
	MBALIGN     equ  1<<0                   ; align modules to page
	MEMINFO     equ  1<<1                   ; memory map
	FLAGS       equ  MBALIGN | MEMINFO      ; mb flag
	MAGIC       equ  0x1BADB002             ; 25
	CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum

global mboot
extern code
extern bss
extern end
	
section .multiboot
align 4
mboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
	dd mboot
		dd code
		dd bss
		dd end
		dd _start

;=>> entry point to the kernel
section .text		
global _start
extern kernel_main

_start:
 	; the jump
	cli
	; set up a stack
	mov esp, stack_top
	push ebx
	mov ebp, 0
	call kernel_main
	jmp $
.end:

; provide stack
section .bss
align 4
	resb 32768
stack_top: