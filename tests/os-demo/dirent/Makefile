LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: dirent

dirent: dirent.o

dirent.o: dirent.c ../utils/utils.h

clean:
	-rm -f *.o *~ dirent
