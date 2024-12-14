CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIC
LDFLAGS = -static-pie

.PHONY: all clean

all: exec-addr

exec-addr: exec-addr.o

clean:
	-rm -f exec-addr.o exec-addr
	-rm -f *~
