CFLAGS = -Wall -fPIE

.PHONY: all clean

all: hello-static hello-dynamic

hello-static: hello.o
	$(CC) -static-pie -fPIE -o $@ $^

hello-dynamic: hello.o
	$(CC) -fPIE -o $@ $^

hello.o: hello.c

clean:
	-rm -f hello.o hello-static hello-dynamic
	-rm -f *~
