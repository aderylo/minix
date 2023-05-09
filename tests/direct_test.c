#include <lib.h>
#include <minix/rs.h>
#include <assert.h>
#include <minix/config.h>
#include <stdio.h>

int main()
{
  message m;
  endpoint_t pm_ep;
  minix_rs_lookup("pm", &pm_ep);

  m.m_lc_pm_waitpid.pid = 1; // pid 
  m.m_lc_pm_waitpid.options = 0; // amount to transfer

  int my_amount = _syscall(pm_ep, PM_TRANSFER_MONEY, &m);

  assert(my_amount == INIT_BALANCE);
  printf("%d\n", my_amount); 
}