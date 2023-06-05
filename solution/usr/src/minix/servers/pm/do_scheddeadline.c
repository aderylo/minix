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
  int64_t deadline = m_in.m_lc_pm_sched.deadline, estimate = m_in.m_lc_pm_sched.estimate;
  int kill = m_in.m_lc_pm_sched.kill;

  struct mproc *process_mproc = find_proc(target_process_pid);

  int already_scheduled = (deadline > -1);
  int stop_sheduling = (deadline == -1);

	int rv;
  message m;
  m.m_pm_sched_scheduling_do_deadline.endpoint = rmp->mp_endpoint;
  m.m_pm_sched_scheduling_do_deadline.deadline = deadline;
  m.m_pm_sched_scheduling_do_deadline.estimate = estimate;
  m.m_pm_sched_scheduling_do_deadline.kill = kill;

  if ((rv = _taskcall(rmp->mp_scheduler, SCHEDULING_DO_DEADLINE, &m))) {
    return rv;
  }

  return (OK);
}
