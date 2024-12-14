/*
 * Imported from the operating systems class.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static void print_current_uid(void)
{
	uid_t uid, euid, ssuid;

	getresuid(&uid, &euid, &ssuid);

	printf("uid: %d; euid: %d; ssuid: %d\n", uid, euid, ssuid);
}

static void drop_privilege(uid_t uid)
{
	if (seteuid(uid) == -1)
		perror("seteuid");
}

static void restore_privilege(uid_t ssuid)
{
	if (seteuid(ssuid) == -1)
		perror("seteuid");
}

static void drop_all(uid_t uid)
{
	if (setresuid(uid, uid, uid) == -1)
		perror("setresuid");
}

int main(void)
{
	uid_t uid, euid, ssuid;
	getresuid(&uid, &euid, &ssuid);

	printf("initial values:\n");
	print_current_uid();

	drop_privilege(uid);
	printf("after privilege drop\n");
	print_current_uid();

	restore_privilege(ssuid);
	printf("after privilege restore\n");
	print_current_uid();

	drop_all(1002);
	printf("drop all privileges\n");
	print_current_uid();

	if (setresuid(1000, 1000, -1) == -1)
		perror("setresuid");
	printf("change real uid to 1000\n");
	print_current_uid();

	if (setresuid(0, 0, -1) == -1)
		perror("setresuid");
	printf("change real uid to 0\n");
	print_current_uid();

	drop_all(1002);
	printf("drop all privileges\n");
	print_current_uid();

	restore_privilege(0);
	printf("try privilege restore\n");
	print_current_uid();

	return 0;
}
