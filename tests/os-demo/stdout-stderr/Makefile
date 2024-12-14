LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: stdout-stderr

stdout-stderr: stdout-stderr.o

open.o: stdout-stderr.c

clean:
	-rm -f *.o *~ stdout-stderr
