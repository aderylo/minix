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

  // start being scheduling with custom strategy
  assert(sched_deadline(1686138424000, 100, false) == 0);

  // resign from this strategy
  assert(sched_deadline(-1, 0, false) == -1);

  // wait to get killed
  assert(sched_deadline(1686138424000, 1, true) == 0); 

  int x = 0; 
  while(true){
    x + x; 
  }

  return x;
}
