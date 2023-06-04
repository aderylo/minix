#include "kernel/system.h"
#include <minix/endpoint.h>
#include "kernel/clock.h"

/*===========================================================================*
 *				do_scheddeadline				     *
 *===========================================================================*/
int do_scheddeadline(struct proc * caller, message * m_ptr)
{
	struct proc *p;
	int proc_nr;
	int deadline, estimate, cpu;

	if (!isokendpt(m_ptr->m_lsys_krn_scheddeadline.endpoint, &proc_nr))
		return EINVAL;

	p = proc_addr(proc_nr);

	/* Only this process' scheduler can schedule it */
	if (caller != p->p_scheduler)
		return(EPERM);

	/* Try to schedule the process. */
	deadline = m_ptr->m_lsys_krn_scheddeadline.deadline;
	estimate = m_ptr->m_lsys_krn_scheddeadline.estimate;
	cpu = m_ptr->m_lsys_krn_scheddeadline.cpu;

	return sched_proc_by_deadline(p, deadline, estimate, cpu);
}
