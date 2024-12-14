LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: indefinite-wait

indefinite-wait: indefinite-wait.o

indefinite-wait.o: indefinite-wait.c ../utils/utils.h

clean:
	-rm -f *.o *~ indefinite-wait
