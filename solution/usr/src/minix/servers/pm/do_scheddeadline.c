#include "pm.h"
#include <minix/config.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "stdio.h"


// struct timespec clock_timespec(void)
// {
// /* This routine returns the time in seconds since 1.1.1970.  MINIX is an
//  * astrophysically naive system that assumes the earth rotates at a constant
//  * rate and that such things as leap seconds do not exist.
//  */
//   static long system_hz = 0;

//   register int k;
//   struct timespec tv;
//   clock_t uptime;
//   clock_t realtime;
//   time_t boottime;

//   if (system_hz == 0) system_hz = sys_hz();
//   if ((k=getuptime(&uptime, &realtime, &boottime)) != OK)
// 	panic("clock_timespec: getuptime failed: %d", k);

//   tv.tv_sec = (time_t) (boottime + (realtime/system_hz));
//   /* We do not want to overflow, and system_hz can be as high as 50kHz */
//   assert(system_hz < LONG_MAX/40000);
//   tv.tv_nsec = (realtime%system_hz) * 40000 / system_hz * 25000;
//   return tv;
// }


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

  return time_sec * 100;  // convert to mili sec
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

  // validate params
  if (deadline < (now + estimate) && deadline != -1) {
    return EINVAL;
  }

  if (!already_scheduled && stop_sheduling) {
    return EPERM;  // can't stop scheduling if not scheduled
  }

  return OK;
}
