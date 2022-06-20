/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The class Semaphore implements the synchronization concept of the         */
/* counting semaphore.                                                       */
/*****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__

/* Add your code here */
#include "meeting/waitingroom.h"

class Semaphore : Waitingroom
/* Add your code here */ 
{
private:
	Semaphore(const Semaphore &copy); // prevent copying
/* Add your code here */ 
	int count;
public:
	Semaphore(int c);
	void p();
	void v();
	inline void wait();
	inline void signal();
};

#endif
