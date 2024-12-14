LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: demand-paging

demand-paging: demand-paging.o

clean:
	-rm -f *.o *~ demand-paging
