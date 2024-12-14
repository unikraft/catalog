LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -Wno-unused-function -g -fPIE

.PHONY: all clean

all: buffer-overflow buffer-overflow-32 buffer-overflow-pie buffer-overflow-ssp buffer-overflow-asan formatstring intovfl oob

oob: oob.o
	$(CC) -no-pie -o $@ $^

oob.o: oob.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -c -o $@ $<

intovfl: intovfl.o
	$(CC) -no-pie -o $@ $^

intovfl.o: intovfl.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -c -o $@ $<

formatstring: formatstring.o
	$(CC) -no-pie -o $@ $^

formatstring.o: formatstring.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -c -o $@ $<

buffer-overflow: buffer-overflow.o
	$(CC) -no-pie -o $@ $^

buffer-overflow.o: buffer-overflow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -c -o $@ $<

buffer-overflow-32: buffer-overflow-32.o
	$(CC) -no-pie -m32 -o $@ $^

buffer-overflow-32.o: buffer-overflow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -m32 -c -o $@ $<

buffer-overflow-pie: buffer-overflow-pie.o
	$(CC) -pie -o $@ $^

buffer-overflow-pie.o: buffer-overflow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fno-stack-protector -fPIC -c -o $@ $<

buffer-overflow-ssp: buffer-overflow-ssp.o
	$(CC) -no-pie -o $@ $^

buffer-overflow-ssp.o: buffer-overflow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fstack-protector -fPIC -c -o $@ $<

buffer-overflow-asan: buffer-overflow-asan.o
	$(CC) -no-pie -fsanitize=address -o $@ $^

buffer-overflow-asan.o: buffer-overflow.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fsanitize=address -fPIC -c -o $@ $<

clean:
	-rm -f buffer-overflow buffer-overflow.o
	-rm -f buffer-overflow-32 buffer-overflow-32.o
	-rm -f buffer-overflow-pie buffer-overflow-pie.o
	-rm -f buffer-overflow-ssp buffer-overflow-ssp.o
	-rm -f buffer-overflow-asan buffer-overflow-asan.o
	-rm -f formatstring formatstring.o
	-rm -f intovfl intovfl.o
	-rm -f oob oob.o
	-rm -f *~
