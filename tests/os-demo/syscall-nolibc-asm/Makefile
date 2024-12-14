LDFLAGS = -m32 -pie

.PHONY: all clean

all: syscall-nolibc

syscall-nolibc: syscall-nolibc.o
	$(CC) $(LDFLAGS) -nostdinc -nostdlib -o $@ $^

syscall-nolibc.o: syscall-nolibc.asm
	nasm -f elf32 -o $@ $<

clean:
	-rm -f *~
	-rm -f syscall-nolibc.o syscall-nolibc
