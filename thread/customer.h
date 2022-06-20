/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Customer class extends the Entrant class with the ability to record   */
/* and retrieve an event that the process in question is waiting for.        */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "meeting/waitingroom.h"
#include "thread/entrant.h"

class Customer : public Entrant {
   private:
    Customer(const Customer& copy);  // prevent copying

    Waitingroom* waitingroom{};

   public:
    Customer(void* tos) : Entrant{tos} {}

    void waiting_in(Waitingroom* w) { waitingroom = w; }

    Waitingroom* waiting_in() { return waitingroom; }
};

#endif
