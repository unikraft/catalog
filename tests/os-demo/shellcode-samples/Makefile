CFLAGS = -Wall -g -fPIE
LDFLAGS = -static-pie

.PHONY: all clean

all: shellcode-samples

shellcode-samples: shellcode-samples.o

shellcode-samples.o: shellcode-samples.c

clean:
	-rm -f shellcode-samples shellcode-samples.o *~
