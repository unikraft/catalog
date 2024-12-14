LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: system-memory

system-memory: system-memory.o

system-memory.o: system-memory.c ../utils/utils.h

clean:
	-rm -f *.o *~ system-memory *.txt
