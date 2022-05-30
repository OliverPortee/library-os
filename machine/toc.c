/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The toc struct is used to save the values of the non-volatile registers   */
/* in case of a context switch. toc_settle prepares the initial stack and    */
/* the toc struct for the first activation.                                  */
/*****************************************************************************/

#include "machine/toc.h"

// TOC_SETTLE: Prepares a coroutine context for its first activation.
void toc_settle(struct toc *regs, void *tos,
		void (*kickoff)(void *, void *, void *, void *, void *, void *,
				void *),
		void *object)
{
	void** p = (void**) tos;

	// push 'object' as parameter for 'kickoff()'
	p -= 1;
	*p = object;

	// push NULL return address for 'kickoff()' as no actual caller exists
	p -= 1;
	*p = 0;

	// push 'kickoff()' address 
	p -= 1;
	*p = kickoff;

	// update stack pointer in 'toc',
	// other register values are irrelevant for first activation
	regs->rsp = p;
}
