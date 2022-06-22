/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Organizer is a special scheduler that additionally allows processes   */
/* (Customer objects) to wait for events (Waitingroom objects).              */
/*****************************************************************************/

#ifndef __organizer_include__
#define __organizer_include__

#include "meeting/waitingroom.h"
#include "thread/customer.h"
#include "thread/scheduler.h"

class Organizer : public Scheduler {
   private:
    Organizer(const Organizer& copy);  // prevent copying
   public:
    Organizer();
    void block(Customer& customer, Waitingroom& waitingroom);
    void wakeup(Customer& customer);
    void kill(Customer& customer);
};

#endif
