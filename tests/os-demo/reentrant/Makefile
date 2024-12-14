LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: reentrant reentrant-ok

reentrant: reentrant.o

reentrant.o: reentrant.c ../utils/utils.h

reentrant-ok: reentrant-ok.o

reentrant-ok.o: reentrant.c ../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -DUSE_REENTRANT -c -o $@ $<

clean:
	-rm -f *.o *~ reentrant reentrant-ok
