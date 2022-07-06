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

#include "meeting/waitingroom.h"

class Semaphore : Waitingroom {
private:
	Semaphore(const Semaphore &copy); // prevent copying
	int count;
public:
	Semaphore(int c);
	void p();
	void v();
	void wait();
	void signal();
};

#endif
