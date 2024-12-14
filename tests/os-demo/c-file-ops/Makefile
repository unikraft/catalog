LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: c-file-ops

c-file-ops: c-file-ops.o

c-file-ops.o: c-file-ops.c ../utils/utils.h

clean:
	-rm -f *.o *~ c-file-ops *.txt
