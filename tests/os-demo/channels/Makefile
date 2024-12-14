LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: channels

channels: channels.o

channels.o: channels.c ../utils/utils.h

clean:
	-rm -f *.o *~ channels *.txt
