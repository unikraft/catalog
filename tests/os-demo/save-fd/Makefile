LDFLAGS = -static-pie
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -g -fPIE

.PHONY: all clean

all: save-fd

save-fd: save-fd.o

save-fd.o: save-fd.c ../utils/utils.h

clean:
	-rm -f *.o *~
	-rm -f *.txt
	-rm -f save-fd
