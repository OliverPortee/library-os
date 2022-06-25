/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Scheduler implementation.                                                 */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "object/queue.h"
#include "thread/dispatch.h"
#include "thread/entrant.h"

class Scheduler : public Dispatcher {
   private:
    Scheduler(const Scheduler& copy);  // prevent copying

   protected:
    Queue queue{};  // of Entrants

   public:
    Scheduler();

    void ready(Entrant& that);

    void schedule();

    void exit();

    void kill(Entrant& that);

    void resume();
};

#endif
