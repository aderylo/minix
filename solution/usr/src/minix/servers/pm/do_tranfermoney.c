#include "pm.h"
#include <minix/config.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"

int do_transfermoney(void)
{
  register struct mproc *rmp = mp;

  pid_t recipient_pid = m_in.m_lc_pm_waitpid.pid;
  int amount = m_in.m_lc_pm_waitpid.options;

  struct mproc *recipient_process_mproc = find_proc(recipient_pid);

  if (recipient_process_mproc == NULL)
  {
    return ESRCH;
  }

  if (amount < 0)
    return EINVAL;

  if (rmp->account_balance - amount < 0)
    return EINVAL;

  if (recipient_process_mproc->account_balance + amount > MAX_BALANCE)
    return EINVAL;

  rmp->account_balance -= amount;
  recipient_process_mproc->account_balance += amount;

  return rmp->account_balance;
}