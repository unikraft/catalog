LDFLAGS = -static-pie
CFLAGS = -Wall -g -fPIE

.PHONY: all clean

all: fork-faults

fork-faults: fork-faults.o

fork-faults.o: fork-faults.c

clean:
	-rm -f *~ *.o fork-faults
