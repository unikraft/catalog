/**
  * Use ioctl calls on CD-ROM drive.
  *
  * Imported from the operating systems class.
  * 
  * Heavily inspired by eject source code: http://eject.sourceforge.net/
  * Documentation in Documentation/ioctl/cdrom.txt in Linux source code.
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <linux/cdrom.h>

#include "../utils/utils.h"

#define CDROM_DEV_PATH		"/dev/sr0"

static void usage(const char *argv0, const char *msg)
{
	fprintf(stderr, "%s\n\n", msg);
	fprintf(stderr, "Usage: %s e|l|u\n", argv0);
	fprintf(stderr, "\te - eject CD-ROM\n");
	fprintf(stderr, "\tl - lock CD-ROM drive\n");
	fprintf(stderr, "\tu - unlock CD-ROM drive\n");
}

static void eject_cdrom(int fd)
{
	int rc;
	rc = ioctl(fd, CDROMEJECT);
	DIE(rc < 0, "ioctl");
}

static void lock_cdrom(int fd)
{
	int rc;
	rc = ioctl(fd, CDROM_LOCKDOOR, 1);
	DIE(rc < 0, "ioctl");
}

static void unlock_cdrom(int fd)
{
	int rc;
	rc = ioctl(fd, CDROM_LOCKDOOR, 0);
	DIE(rc < 0, "ioctl");
}

int main(int argc, char **argv)
{
	int fd;

	if (argc != 2) {
		usage(argv[0], "You must provide exactly one argument.");
		exit(EXIT_FAILURE);
	}
	if (strlen(argv[1]) != 1) {
		usage(argv[0], "Argument must be e or l or u.");
		exit(EXIT_FAILURE);
	}

	fd = open(CDROM_DEV_PATH, O_RDONLY | O_NONBLOCK);
	DIE(fd < 0, "open");

	switch (argv[1][0]) {
	case 'e':
		eject_cdrom(fd);
		break;
	case 'l':
		lock_cdrom(fd);
		break;
	case 'u':
		unlock_cdrom(fd);
		break;
	default:
		usage(argv[0], "Argument must be e or l or u.");
		exit(EXIT_FAILURE);
		break;
	}

	close(fd);
	return 0;
}
