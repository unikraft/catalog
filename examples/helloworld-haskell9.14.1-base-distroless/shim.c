#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

int clock_gettime(clockid_t clock_id, struct timespec *tp) {
  if (clock_id == 2 || clock_id == 3)
    clock_id = 1; /* CPUTIME -> MONOTONIC */
  return syscall(SYS_clock_gettime, clock_id, tp);
}
