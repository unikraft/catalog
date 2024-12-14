LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: spinlock mutex

spinlock: spinlock.o

spinlock.o: spinlock-mutex.c ../utils/utils.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -D USE_SPINLOCK -c -o $@ $<

mutex: mutex.o

mutex.o: spinlock-mutex.c ../utils/utils.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	-rm -f *.o *~ spinlock mutex
