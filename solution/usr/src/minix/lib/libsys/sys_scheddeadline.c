#include "syslib.h"

int sys_scheddeadline(endpoint_t proc_ep,
			int64_t deadline,
			int64_t estimate,
			int cpu)
{
	message m;

	m.m_lsys_krn_scheddeadline.endpoint = proc_ep;
	m.m_lsys_krn_scheddeadline.deadline = deadline;
	m.m_lsys_krn_scheddeadline.estimate  = estimate;
	m.m_lsys_krn_scheddeadline.cpu = cpu;
	return(_kernel_call(SYS_SCHEDDEADLINE, &m));
}