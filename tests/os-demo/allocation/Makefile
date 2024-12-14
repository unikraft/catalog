LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: allocation

allocation: allocation.o

clean:
	-rm -f *.o *~ allocation
