LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: orphan zombie

orphan: orphan.o

orphan.o: orphan.c ../utils/utils.h

zombie: zombie.o

zombie.o: zombie.c ../utils/utils.h

clean:
	-rm -f *.o *~ orphan zombie
