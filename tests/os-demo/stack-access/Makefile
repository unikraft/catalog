LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: stack-access

stack-access: stack-access.o

stack-access.o: stack-access.c ../utils/utils.h

clean:
	-rm -f *.o *~ stack-access
