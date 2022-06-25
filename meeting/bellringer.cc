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

void Bellringer::check() {
    auto* bell = static_cast<Bell*>(first());
    while (bell != nullptr) {
        bell->tick();
        if (bell->run_down()) {
            bell->ring();
            remove(bell);
        }
        bell = static_cast<Bell*>(bell->next);
    }
    
}

void Bellringer::job(Bell* bell, int ticks) {
    bell->wait(ticks);
    enqueue(bell);
}

void Bellringer::cancel(Bell* bell) {
    remove(bell);
}

Bellringer bellringer{};