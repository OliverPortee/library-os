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

class Customer;

class Waitingroom : public Queue {
   private:
    Waitingroom(const Waitingroom& copy);  // prevent copying

   public:
    Waitingroom();
    virtual ~Waitingroom();
    virtual void remove(Customer* customer);
};

#endif
