LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: address-space-threads

address-space-threads: address-space-threads.o

address-space-threads.o: address-space-threads.c ../utils/utils.h

clean:
	-rm -f *.o *~ address-space-threads
