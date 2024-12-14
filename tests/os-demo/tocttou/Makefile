LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: tocttou

tocttou: tocttou.o

tocttou.o: tocttou.c ../utils/utils.h

clean:
	-rm -f *.o *~ tocttou
