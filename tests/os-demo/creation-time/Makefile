LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: process-overhead thread-overhead

process-overhead: process-overhead.o

process-overhead.o: process-overhead.c ../utils/utils.h

thread-overhead: thread-overhead.o

thread-overhead.o: thread-overhead.c ../utils/utils.h

clean:
	-rm -f *.o *~ process-overhead thread-overhead
