/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "../utils/utils.h"

int main(void)
{
    int fd;
    size_t i;

    for (i = 0; i < 10; i++) {
        write(STDOUT_FILENO, "a", 1);
        sleep(1);
    }
    write(STDOUT_FILENO, "\n", 1);

    fd = open("f.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    DIE(fd < 0, "open");

    for (i = 0; i < 10; i++) {
        write(fd, "a", 1);
        write(fd, "\n", 1);
        sleep(1);
    }

    close(fd);

    return 0;
}
