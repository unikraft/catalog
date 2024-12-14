#CPPFLAGS = -DDEBUG -DLOG_LEVEL=LOG_DEBUG
CFLAGS = -Wall -Wextra -Wno-unused-parameter -g -fPIC
LDFLAGS = -pie

.PHONY: all clean

build: all

all: epoll-server server sendfile-server threaded-server

epoll-server: epoll-server.o sock-util.o
	$(CC) $(LDFLAGS) -o $@ $^

server: server.o sock-util.o
	$(CC) $(LDFLAGS) -o $@ $^

sendfile-server: sendfile-server.o sock-util.o
	$(CC) $(LDFLAGS) -o $@ $^

threaded-server: threaded-server.o sock-util.o
	$(CC) $(LDFLAGS) -o $@ $^ -lpthread

epoll-server.o: epoll-server.c sock-util.h debug.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

server.o: server.c sock-util.h debug.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

sendfile-server.o: sendfile-server.c sock-util.h debug.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

threaded-server.o: threaded-server.c sock-util.h debug.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

sock-util.o: sock-util.c sock-util.h debug.h util.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -f *~
	-rm -f *.o
	-rm -f epoll-server server sendfile-server threaded-server