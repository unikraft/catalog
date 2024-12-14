LDFLAGS = -static-pie
CC = gcc
CPPFLAGS = -I../utils
CFLAGS = -Wall -Wextra -fPIE

.PHONY: all clean

all: cdrom-ioctl hwaddr-ioctl

cdrom-ioctl: cdrom-ioctl.o

cdrom-ioctl.o: cdrom-ioctl.c ../utils/utils.h

haddr-iowctl: hwaddr-ioctl.o

hwaddr-ioctl.o: hwaddr-ioctl.c ../utils/utils.h

clean:
	-rm -f *.o *~ cdrom-ioctl hwaddr-ioctl
