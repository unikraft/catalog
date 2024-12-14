LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: allocation-granularity

allocation-granularity: allocation-granularity.o

allocation-granularity.o: allocation-granularity.c ../utils/utils.h

clean:
	-rm -f *.o *~ allocation-granularity *.txt
