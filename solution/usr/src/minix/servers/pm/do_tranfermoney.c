#include "pm.h"
#include <minix/config.h>
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "stdio.h"


int is_ancestor_of(struct mproc *rmp, pid_t pid) {
  while (rmp->mp_pid != 1) {
    rmp = &mproc[rmp->mp_parent];

    if (rmp->mp_pid == pid)
      return OK;
  }

  return (-1);
}

int do_transfermoney(void) {
  register struct mproc *sender_mp = mp;
  pid_t sender_pid = sender_mp->mp_pid; 

  pid_t recipient_pid = m_in.m_lc_pm_waitpid.pid;
  int amount = m_in.m_lc_pm_waitpid.options;

  register struct mproc *recipient_mp = find_proc(recipient_pid);

  if (recipient_mp == NULL)
    return ESRCH;
    
  if (is_ancestor_of(sender_mp, recipient_pid) == OK)
    return EPERM;

  if (is_ancestor_of(recipient_mp, sender_pid) == OK)
    return EPERM; 

  if (amount < 0)
    return EINVAL;

  if (sender_mp->account_balance - amount < 0)
    return EINVAL;

  if (recipient_mp->account_balance + amount > MAX_BALANCE)
    return EINVAL;

  sender_mp->account_balance -= amount;
  recipient_mp->account_balance += amount;
  sender_mp->mp_reply.m_lc_pm_waitpid.options = sender_mp->account_balance;

  return OK;
}