CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -fPIC -g -fPIE
LDFLAGS = -static-pie
LDLIBS = -lpthread

.PHONY: all clean

all: sum-threads sum-threads-atomic

sum-threads: sum-threads.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

sum-threads.o: sum-threads.c ../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

sum-threads-atomic: sum-threads-atomic.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

sum-threads-atomic.o: sum-threads.c ../utils/utils.h
	$(CC) $(CPPFLAGS) -DUSE_ATOMIC $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f sum-threads.o sum-threads
	-rm -f sum-threads-atomic.o sum-threads-atomic
