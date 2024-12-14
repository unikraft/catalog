NASM = nasm
GCC = gcc
LDFLAGS = -static-pie

.PHONY: all clean

all: hello-nasm hello-gas

hello-nasm: hello-nasm.o

hello-gas: hello-gas.o

hello-gas.o: hello.s
	$(GCC) -c -o $@ $<

hello-nasm.o: hello.asm
	$(NASM) -f elf64 -o $@ $<

clean:
	-rm -f hello-nasm.o hello-nasm
	-rm -f hello-gas.o hello-gas
	-rm -f *~