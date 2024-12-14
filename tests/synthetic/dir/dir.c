#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(void)
{
	DIR *d;
	struct dirent *de;

	d = opendir("/");
	if (d == NULL) {
		perror("opendir");
		exit(EXIT_FAILURE);
	}

	while (1) {
		errno = 0;
		de = readdir(d);
		if (de == NULL) {
			if (errno == 0)
				break;
			perror("readdir");
			exit(EXIT_FAILURE);
		}
		printf("de->d_name: %s, type: %u\n", de->d_name, de->d_type);
	}

	closedir(d);

	return 0;
}
