LDFLAGS = -static-pie
CFLAGS = -Wall -g -fPIE

.PHONY: all move clean

all: move

move: setuid
	chown root:root setuid
	chmod u+s setuid

setuid: setuid.o

setuid.o: setuid.c

clean:
	-sudo rm -f setuid
	-rm -f *~
	-rm -f *.o
