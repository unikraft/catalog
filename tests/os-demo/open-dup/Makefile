LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: open dup

open: open.o

open.o: open.c ../utils/utils.h

dup: dup.o

dup.o: dup.c ../utils/utils.h

clean:
	-rm -f *.o *~ open dup *.txt
