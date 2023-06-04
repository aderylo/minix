#include <assert.h>
#include <errno.h>
#include <minix/config.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <lib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>
#include <stdbool.h>

int sched_deadline(int64_t deadline, int64_t estimate, bool kill)
{
  message mess;

  endpoint_t pm_ep;
  if (minix_rs_lookup("pm", &pm_ep) != 0)
  {
    errno = ENOSYS;
    return (-1);
  }

  mess.m_lc_pm_sched.pid = getpid();
  mess.m_lc_pm_sched.deadline = deadline;
  mess.m_lc_pm_sched.estimate = estimate;
  mess.m_lc_pm_sched.kill = kill;

  if (_syscall(pm_ep, PM_SCHED_DEADLINE, &mess) < 0)
  {
    return (-1);
  }

  return 0;
}
