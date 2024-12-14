LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: pipe

pipe: pipe.o

pipe.o: pipe.c ../utils/utils.h

clean:
	-rm -f *.o *~ pipe
