extern printf

section .rodata
	message db "anaaremere", 10, 0
	len equ $-message

section .text

global main

main:
	push ebp
	mov ebp, esp

	push message
	call printf
	add esp, 4

	mov ebx, 1
	mov ecx, message
	mov edx, len
	mov eax, 4
	int 0x80

	leave
	ret
