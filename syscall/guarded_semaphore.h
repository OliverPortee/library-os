/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Semaphore class implements the system call interface to the   */
/* Semaphore class.                                                          */
/*****************************************************************************/

#ifndef __Guarded_Semaphore_include__
#define __Guarded_Semaphore_include__

/* Add your code here */ 
#include "meeting/semaphore.h"

class Guarded_Semaphore : Semaphore
/* Add your code here */ 
{
private:
	Guarded_Semaphore(const Guarded_Semaphore &copy); // prevent copying
/* Add your code here */ 
public:
	Guarded_Semaphore(int c);
	void p();
	void v();
	inline void wait();
	inline void signal();
};

#endif
