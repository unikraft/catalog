CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fno-stack-protector -fPIE
LDFLAGS = -static-pie

.PHONY: all clean

all: run-shellcode inject-shellcode

run-shellcode: run-shellcode.o

inject-shellcode: inject-shellcode.o
	$(CC) $(LDFLAGS) -z execstack -o $@ $^

clean:
	-rm -f run-shellcode.o run-shellcode
	-rm -f inject-shellcode.o inject-shellcode
	-rm -f *~
