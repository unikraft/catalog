LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: sparse-file

sparse-file: sparse-file.o

open.o: sparse-file.c

clean:
	-rm -f *.o *~ sparse-file
