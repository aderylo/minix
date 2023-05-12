#include <assert.h>
#include <errno.h>
#include <minix/config.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  errno = 0;

  int result = transfermoney(4567, 0);
  assert(result == -1);
  assert(errno == ESRCH);

  result = transfermoney(getpid(), 0);
  assert(result == 100);

  result = transfermoney(getpid(), -1);
  assert(result == -1);
  assert(errno == EINVAL);

  result = transfermoney(getpid(), 1000);
  assert(result == -1);
  assert(errno == EINVAL);

  result = transfermoney(1, 200);
  assert(result == -1);
  assert(errno == EINVAL);

  return 0;
}