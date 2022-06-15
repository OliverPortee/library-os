/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements a list of processes (Customer objects) that are all waiting    */
/* for a specific event.                                                     */
/*****************************************************************************/

#ifndef __waitingroom_include__
#define __waitingroom_include__

#include "object/queue.h"
#include "thread/customer.h"

class Customer; // Forward declaration

class Waitingroom : public Queue {
private:
	Waitingroom(const Waitingroom &copy); // prevent copying
public:
	Waitingroom() {}
/* Add your code here */ 
};

#endif
