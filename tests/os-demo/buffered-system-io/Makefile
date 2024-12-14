LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: buffered system

buffered: buffered.o

buffered.o: buffered.c ../utils/utils.h

system: system.o

system.o: system.c ../utils/utils.h

clean:
	-rm -f *.o *~ buffered system *.txt
