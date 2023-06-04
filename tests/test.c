#include <assert.h>
#include <errno.h>
#include <minix/config.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>


/*
  int sched_deadline(int64_t deadline, int64_t estimate, bool kill);
*/

int main()
{
  errno = 0;

  // try to resign from custom scheduling queue while not being in there
  assert(sched_deadline(-1, 1, true) == -1);
  assert(errno == EPERM);

  // bad deadline arg, i.e. deadline < (now )
  assert(sched_deadline(0, 10, false) == -1);
  assert(errno == EINVAL);

  assert(sched_deadline(1686138424000, 100, true) == 0);

  return 0;
}
