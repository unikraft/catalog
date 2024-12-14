LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: pmap

pmap: pmap.o

pmap.o: pmap.c ../utils/utils.h


clean:
	-rm -f *.o *~ pmap
