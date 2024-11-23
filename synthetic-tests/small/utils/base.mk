LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: all clean

all: $(BIN)

$(BIN): $(BIN).o

$(BIN).o: $(BIN).c ../utils/utils.h

clean:
	-rm -f $(BIN) $(BIN).o
	-rm -f *~
