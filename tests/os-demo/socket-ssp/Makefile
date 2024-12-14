CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused-function -g -fstack-protector -fPIE
LDFLAGS = -static-pie

.PHONY: all clean

all: socket-ssp

socket-ssp: socket-ssp.o

clean:
	-rm -f socket-ssp.o socket-ssp
	-rm -f *~
