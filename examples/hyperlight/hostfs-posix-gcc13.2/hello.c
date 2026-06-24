/*
 * Transparent POSIX filesystem access on Hyperlight.
 *
 * The Unikraft kernel auto-mounts `hostfs` at /host; every open/read/
 * write/mkdir/stat under that tree becomes an __dispatch RPC to the
 * host's FsSandbox, which is scoped to the directory the host passed
 * via `--mount`.
 *
 * This program uses only standard POSIX — no hcall helpers, no JSON —
 * demonstrating that unmodified code runs against a sandboxed host
 * directory.
 *
 * Note: opendir/readdir are not exercised here; see the known
 * limitations in the hostfs README.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void die(const char *op, const char *path)
{
	fprintf(stderr, "%s %s: %s\n", op, path, strerror(errno));
}

int main(void)
{
	puts("hostfs-posix-c: unmodified POSIX against the sandboxed host mount");

	/* 1. Write a file. */
	int fd = open("/host/greeting.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0) { die("open", "/host/greeting.txt"); return 1; }
	const char *msg = "Hello from Unikraft via transparent POSIX!\n"
			  "No hcall helpers — just open + write.\n";
	ssize_t n = write(fd, msg, strlen(msg));
	printf("wrote /host/greeting.txt (%zd bytes)\n", n);
	close(fd);

	/* 2. Read it back. */
	fd = open("/host/greeting.txt", O_RDONLY);
	if (fd < 0) { die("open", "/host/greeting.txt"); return 1; }
	char buf[1024];
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n < 0) { die("read", "/host/greeting.txt"); return 1; }
	buf[n] = '\0';
	printf("read (%zd bytes):\n---\n%s---\n", n, buf);

	/* 3. Create a subdirectory and append to a file in it. */
	if (mkdir("/host/logs", 0777) < 0 && errno != EEXIST) {
		die("mkdir", "/host/logs");
		return 1;
	}
	fd = open("/host/logs/app.log", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd < 0) { die("open append", "/host/logs/app.log"); return 1; }
	write(fd, "line 1\n", 7);
	write(fd, "line 2\n", 7);
	close(fd);
	puts("appended to /host/logs/app.log");

	/* 4. stat. */
	struct stat st;
	if (stat("/host/greeting.txt", &st) == 0)
		printf("stat: size=%lld\n", (long long)st.st_size);

	/* Sandbox escape scenarios that the host refuses (proven by
	 * the Rust-side FsSandbox tests in host/src/lib.rs):
	 *
	 *   - "..": path components resolving above the mount root
	 *   - absolute "/etc/passwd" re-interpreted as under the mount
	 *   - symlinks inside the mount pointing to an outside path
	 *
	 * We'd open() a planted symlink here to demo it live, but the
	 * Unikraft build we target currently crashes on any open() that
	 * returns an error (vfscore namei cleanup bug — reproduces with
	 * open("/nonexistent") against plain ramfs too). Tracked
	 * separately; not a hostfs issue.
	 */

	puts("done.");
	return 0;
}
