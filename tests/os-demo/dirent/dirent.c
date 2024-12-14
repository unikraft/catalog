/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#include "../utils/utils.h"

static char dentry_type_buffer[256];

static char *get_entry_type(const struct dirent *de)
{
	switch (de->d_type) {
	case DT_BLK:
		strncpy(dentry_type_buffer, "block device", 13);
		break;
	case DT_CHR:
		strncpy(dentry_type_buffer, "character device", 17);
		break;
	case DT_DIR:
		strncpy(dentry_type_buffer, "directory", 10);
		break;
	case DT_FIFO:
		strncpy(dentry_type_buffer, "named pipe (FIFO)", 18);
		break;
	case DT_LNK:
		strncpy(dentry_type_buffer, "symbolic link", 14);
		break;
	case DT_REG:
		strncpy(dentry_type_buffer, "regular file", 13);
		break;
	case DT_SOCK:
		strncpy(dentry_type_buffer, "domain file", 12);
		break;
	default:
		strncpy(dentry_type_buffer, "unknown", 7);
		break;
	}

	return dentry_type_buffer;
}

int main(int argc, char **argv)
{
	char *dirname;
	DIR *dirp;
	struct dirent *de;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s folder-name\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	dirname = argv[1];
	dirp = opendir(dirname);
	DIE(dirp == NULL, "dirname");

	printf("-- Reading directory %s\n\n", dirname);
	while (1) {
		de = readdir(dirp);
		if (de == NULL)
			break;
		printf("%s [%s]\n", de->d_name, get_entry_type(de));
	}

	return 0;
}
