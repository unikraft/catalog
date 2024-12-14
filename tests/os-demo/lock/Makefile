CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -fPIE -g
LDFLAGS = -static-pie
LDLIBS = -lpthread

.PHONY: all clean

all: lock lock_atomic lock_spin

lock: lock.o

lock.o: lock.c ../utils/utils.h

lock_atomic: lock_atomic.o

lock_atomic.o: lock.c ../utils/utils.h
	$(CC) $(CPPFLAGS) -DUSE_ATOMIC $(CFLAGS) -c -o $@ $<

lock_spin: lock_spin.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

lock_spin.o: lock.c ../utils/utils.h
	$(CC) $(CPPFLAGS) -DUSE_SPINLOCK $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f lock.o lock
	-rm -f lock_atomic.o lock_atomic
	-rm -f lock_spin.o lock_spin
