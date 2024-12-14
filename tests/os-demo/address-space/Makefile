CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE
LDFLAGS = -static-pie

.PHONY: all clean

all: address-space

address-space: address-space.o

address-space.o: address-space.c ../utils/utils.h

clean:
	-rm -f *.o *~ address-space *.txt
