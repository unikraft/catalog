LDFLAGS = -static-pie
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: fopen-perm

fopen-perm: fopen-perm.o

fopen-perm.o: fopen-perm.c

clean:
	-rm -f *~
	-rm -f fopen-perm.o fopen-perm

