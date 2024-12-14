LDFLAGS = -m32 -pie

.PHONY: all clean

all: syscall-libc-call syscall-libc-call-static

syscall-libc-call-static: syscall-libc-call.o
	$(CC) $(LDFLAGS) -o $@ $^

syscall-libc-call: syscall-libc-call.o

syscall-libc-call.o: syscall-libc-call.asm
	nasm -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f syscall-libc-call.o syscall-libc-call syscall-libc-call-static
