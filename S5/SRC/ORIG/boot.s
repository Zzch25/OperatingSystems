[BITS 32]

; Declare constants used for creating a multiboot header.
	MBALIGN     equ  1<<0                   ; align modules to page
	MEMINFO     equ  1<<1                   ; memory map
	FLAGS       equ  MBALIGN | MEMINFO      ; mb flag
	MAGIC       equ  0x1BADB002             ; 25
	CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum

section .__mbHeader 
align 4

; Multiboot Standard
mboot:
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
; provide stack
section .bootstrap_stack
align 4
stack_bottom:
times 16384 db 0
stack_top:
 
; entry point to the kernel
section .text
global _start
_start:
 
	; set up a stack
	mov esp, stack_top
 
	; yey CPP
	extern kernel_main
	call kernel_main

	cli
.hang:
	hlt
	jmp .hang