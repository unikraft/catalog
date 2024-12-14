LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: deadlock

deadlock: deadlock.o

deadlock.o: deadlock.c ../utils/utils.h

clean:
	-rm -f *.o *~ deadlock
