LDFLAGS = -static-pie
CFLAGS = -Wall -fPIE

.PHONY: all clean

all: caller

caller: caller.o

caller.o: caller.c

clean:
	-rm -f *~
	-rm -f caller.o caller
