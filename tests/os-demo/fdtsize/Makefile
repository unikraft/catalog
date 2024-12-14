LDFLAGS = -static-pie
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: fdtsize

fdtsize: fdtsize.o

fdtsize.o: fdtsize.c

clean:
	-rm -f *~
	-rm -f fdtsize.o fdtsize

