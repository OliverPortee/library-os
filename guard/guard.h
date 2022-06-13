/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Using this class, we can synchronize activities with a critical section   */
/* with interrupt handlers that also access this critical section. This      */
/* synchronization takes place along the prologue/epilogue model.            */
/*****************************************************************************/

#ifndef __Guard_include__
#define __Guard_include__

#include "object/queue.h"
#include "guard/locker.h"
#include "guard/gate.h"

class Guard : public Locker {
private:
	Guard (const Guard &copy); // prevent copying

	Queue queue;

public:
	Guard () {}

	void leave();
	void relay(Gate* item);
};

extern Guard guard;

#endif
