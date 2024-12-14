LDFLAGS = -static-pie
CC = gcc
DC = gdc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: executor executor_ansi printer executor_spawn executor_system

executor_system: executor_system.o

executor_system.o: executor_system.c ../utils/utils.h

executor_spawn: executor_spawn.o

executor_spawn.o: executor_spawn.c ../utils/utils.h

executor: executor.o

executor.o: executor.c ../utils/utils.h

executor_ansi: executor_ansi.o

executor_ansi.o: executor_ansi.c ../utils/utils.h

printer: printer.o
	$(DC) -o $@ $^

printer.o: printer.d
	$(DC) -c -o $@ $<

clean:
	-rm -f executor executor.o
	-rm -f executor_spawn executor_spawn.o
	-rm -f executor_system executor_system.o
	-rm -f executor_ansi executor_ansi.o
	-rm -f printer printer.o
	-rm -f *~
