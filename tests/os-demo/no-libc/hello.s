.section .data

hello:
	.ascii "Hello, world!\n\0"

.section .text

.global main

main:
	push %rbp
	mov %rsp, %rbp

	# Call write(1, "Hello, world!\n", 14).
	# rax <- __NR_write (index of write syscall: 1)
	# rdi <- first syscall argument (fd: 1)
	# rsi <- second syscall argument (buffer: hello)
	# rdx <- third syscall argument (lenght: 14)
	mov $1, %rdi
	lea hello(%rip), %rsi
	mov $14, %rdx
	mov $1, %rax
	syscall

	# Call exit(0).
	# rax <- __NR_exit (index of exit syscall: 60)
	# rdi <- first syscall argument (error_code: 0)
	mov $0, %rdi
	mov $60, %rax
	syscall

	xor %rax, %rax
	leave
	ret
