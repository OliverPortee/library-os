/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The "bell ringer" (Bellringer) is activated periodically and checks if    */
/* any "bells" (Bell objects) need to ring. The bells are in a list that the */
/* bellringer manages.                                                       */
/*****************************************************************************/

#include "meeting/bellringer.h"
#include "object/assert.h"

void Bellringer::check() {
    auto* bell = static_cast<Bell*>(first());
    while (bell != nullptr) {
        bell->tick();
        if (bell->run_down()) {
            bell->ring();
            auto next_bell = bell->next;
            remove(bell);
            bell = static_cast<Bell*>(next_bell);
        } else {
            bell = static_cast<Bell*>(bell->next);
        }
    }
    
}

void Bellringer::job(Bell* bell, int ticks) {
    assert(ticks > 0, "Bellringer::job with ticks <= 0");
    bell->wait(ticks);
    enqueue(bell);
}

void Bellringer::cancel(Bell* bell) {
    remove(bell);
}

Bellringer bellringer{};