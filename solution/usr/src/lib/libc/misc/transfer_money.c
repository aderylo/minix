#include <lib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int transfermoney(pid_t recipient, int amount)
{
  message mess;

  endpoint_t pm_ep;
  if (minix_rs_lookup("pm", &pm_ep) != 0)
  {
    errno = ENOSYS;
    return (-1);
  }

  mess.m_lc_pm_waitpid.pid = recipient;
  mess.m_lc_pm_waitpid.options = amount;

  if (_syscall(pm_ep, PM_TRANSFER_MONEY, &mess) < 0)
  {
    return (-1);
  }

  return mess.m_lc_pm_waitpid.options;
}
