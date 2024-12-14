section .rodata
	message db "anaaremere", 10, 0
	len equ $-message

section .text

global main
global _start

_start:
	call main

	mov ebx, 0
	mov eax, 1
	int 0x80


main:
	push ebp
	mov ebp, esp

	mov ebx, 1
	lea ecx, [rel message]
	mov edx, len
	mov eax, 4
	int 0x80

	leave
	ret
