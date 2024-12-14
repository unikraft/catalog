LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused-but-set-variable -Wno-discarded-qualifiers -g -fPIE

.PHONY: all clean

all: access-permissions

access-permissions: access-permissions.o

access-permissions.o: access-permissions.c ../utils/utils.h

clean:
	-rm -f access-permissions.o access-permissions
	-rm -f *~
