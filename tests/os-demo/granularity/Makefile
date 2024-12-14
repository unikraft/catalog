LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: clean

all: granularity-fine granularity-coarse

granularity-fine: granularity-fine.o

granularity-fine.o: granularity.c ../utils/utils.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -DGRANULARITY_TYPE=2 -c -o $@ $<

granularity-coarse: granularity-coarse.o

granularity-coarse.o: granularity.c ../utils/utils.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -DGRANULARITY_TYPE=1 -c -o $@ $<

clean:
	rm -f *.o *~ granularity-fine granularity-coarse
