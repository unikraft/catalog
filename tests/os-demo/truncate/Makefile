LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: truncate

truncate: truncate.o

open.o: truncate.c

clean:
	-rm -f *.o *~ truncate
