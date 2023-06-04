#include "pm.h"
#include <minix/config.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "stdio.h"


int do_scheddeadline(void) {
  register struct mproc *rmp = mp;

  pid_t target_process_pid = m_in.m_lc_pm_sched.pid;
  int deadline = m_in.m_lc_pm_sched.deadline, estimate = m_in.m_lc_pm_sched.estimate,
      kill = m_in.m_lc_pm_sched.kill;

  struct mproc *process_mproc = find_proc(target_process_pid);

  int now = 100;
  int already_scheduled = (deadline > -1);
  int stop_sheduling = (deadline == -1);

  if (!already_scheduled && stop_sheduling) {
    return EPERM;  // can't stop scheduling if not scheduled
  }

  return OK;
}
  