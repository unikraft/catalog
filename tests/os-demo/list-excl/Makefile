LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused -Wno-unused-parameter -g -fPIE
LDLIBS = -lpthread

.PHONY: clean

all: thread-list-app thread-list-app-mutex

thread-list-app-mutex: thread-list-app-mutex.o list.o

thread-list-app-mutex.o: thread-list-app.c list.h ../utils/utils.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -D USE_MUTEX

thread-list-app: thread-list-app.o list.o

thread-list-app.o: thread-list-app.c list.h ../utils/utils.h

list.o: list.c ../utils/utils.h

clean:
	-rm -f *.o *~ thread-list-app thread-list-app-mutex
