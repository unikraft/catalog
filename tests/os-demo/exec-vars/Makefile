LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -g -fPIE

.PHONY: all clean

all: exec-vars

exec-vars: exec-vars.o

exec-vars.o: exec-vars.c ../utils/utils.h

clean:
	-rm -f *.o *~ exec-vars
