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

#include "guard.h"

#include "guard/secure.h"
#include "machine/cpu.h"

void Guard::leave() {
    Chain* chain;
    cpu.disable_int();
    while ((chain = queue.dequeue())) {
        Gate* gate = static_cast<Gate*>(chain);
        gate->queue(false);
        cpu.enable_int();
        gate->epilogue();
        cpu.disable_int();
    }
    retne();
    cpu.enable_int();
}

void Guard::relay(Gate* item) {
    if (!item->queued()) {
        if (avail()) {
            Secure secure;
            cpu.enable_int();
            item->epilogue();
        } else {
            item->queue(true);
            queue.enqueue(item);
        }
    }
}

Guard guard{};