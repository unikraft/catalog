LDFLAGS = -static-pie
CC = gcc
DC = gdc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: executor executor_ansi reader writer

executor: executor.o

executor.o: executor.c ../utils/utils.h

executor_ansi: executor_ansi.o

executor_ansi.o: executor_ansi.c ../utils/utils.h

reader: reader.o
	$(DC) -o $@ $^

reader.o: reader.d
	$(DC) -c -o $@ $<

writer: writer.o
	$(DC) -o $@ $^

writer.o: writer.d
	$(DC) -c -o $@ $<

clean:
	-rm -f executor executor.o
	-rm -f executor_ansi executor_ansi.o
	-rm -f reader reader.o
	-rm -f writer writer.o
	-rm -f *~
