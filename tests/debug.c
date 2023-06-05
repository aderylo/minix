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
  int rv;
  // try to resign from custom scheduling queue while not being in there
  rv = sched_deadline(-1, 1, true);
  printf("%d  %d\n", errno, rv);

  rv = sched_deadline(-1, 1, true);
  printf("%d  %d\n", errno, rv);

  // assert(errno == EPERM);

  // bad deadline arg, i.e. deadline < (now )
  rv = sched_deadline(0, 10, false);
  printf("%d  %d\n", errno, rv);

  // assert(errno == EINVAL);

  errno = 0;

  // start being scheduling with custom strategy
  rv = sched_deadline(1686138424000, 100, false);
  printf("%d  %d\n", errno, rv);

  // resign from this strategy
  rv = sched_deadline(-1, 0, false);
  printf("%d  %d\n", errno, rv);

  // wait to get killed
  rv = sched_deadline(1686138424000, 1, true);
  printf("%d  %d\n", errno, rv);


  int x = 0; 
  while(true){
    x + x; 
  }

  return x;
}
