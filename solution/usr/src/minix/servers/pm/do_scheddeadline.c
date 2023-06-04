#include "pm.h"
#include <minix/config.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "stdio.h"

int64_t current_time_miliseconds() {
  static long system_hz = 0;

  register int k;
  long uptime, realtime;
  time_t boottime;
  int64_t time_sec;

  if (system_hz == 0)
    system_hz = sys_hz();
  if ((k = getuptime(&uptime, &realtime, &boottime)) != OK)
    panic("clock_timespec: getuptime failed: %d", k);

  /* We do not want to overflow, and system_hz can be as high as 50kHz */
  time_sec = (boottime + (realtime / system_hz));

  return time_sec * 1000;  // convert to mili sec
}

int do_scheddeadline(void) {
  register struct mproc *rmp = mp;

  pid_t target_process_pid = m_in.m_lc_pm_sched.pid;
  int64_t deadline = m_in.m_lc_pm_sched.deadline, estimate = m_in.m_lc_pm_sched.estimate;
  int kill = m_in.m_lc_pm_sched.kill;
  int64_t now = current_time_miliseconds();

  struct mproc *process_mproc = find_proc(target_process_pid);

  int already_scheduled = (deadline > -1);
  int stop_sheduling = (deadline == -1);

  // printf("%lld\n" , now);

  // validate params
  if (deadline < (now + estimate) && deadline != -1) {
    return EINVAL;  // the process is already late given its deadline
  }

  if (!already_scheduled && stop_sheduling) {
    return EPERM;  // can't stop scheduling if not scheduled
  }

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
