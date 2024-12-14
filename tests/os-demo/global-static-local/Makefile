LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: global-static-local

global-static-local: global-static-local.o

global-static-local.o: global-static-local.c ../utils/utils.h

clean:
	-rm -f *.o *~ global-static-local
