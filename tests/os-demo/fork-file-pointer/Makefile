LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: fork-file-pointer

fork-file-pointer: fork-file-pointer.o

fork-file-pointer.o: fork-file-pointer.c ../utils/utils.h

clean:
	-rm -f *.o *~ fork-file-pointer *.txt
