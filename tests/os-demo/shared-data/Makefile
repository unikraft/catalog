LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unsed -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: process thread

process: process.o

process.o: process.c ../utils/utils.h

thread: thread.o

thread.o: thread.c ../utils/utils.h

clean:
	-rm -f *.o *~ process thread
