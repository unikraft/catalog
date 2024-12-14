LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: cpu io

cpu: cpu.o

cpu.o: cpu.c ../utils/utils.h

io: io.o

io.o: io.c ../utils/utils.h

clean:
	-rm -f *.o *~ cpu io
