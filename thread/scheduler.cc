/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Scheduler implementation.                                                 */
/*****************************************************************************/

#include "thread/scheduler.h"
#include "guard/secure.h"

Scheduler::Scheduler() {}

void Scheduler::ready(Entrant& that) {
    Secure secure;
    queue.enqueue(&that);
}

void Scheduler::schedule() {
    // TODO: Secure?
    Chain* chain = queue.dequeue();
    Entrant* e = static_cast<Entrant*>(chain);
    Coroutine* coroutine = static_cast<Coroutine*>(e);

    if(active() == nullptr) {
        go(*coroutine);
    } else {
        dispatch(*coroutine);
    }
}

void Scheduler::exit() {
    schedule(); // doesn't make much sense to have a separate method for that
}

void Scheduler::kill(Entrant& that) {
    Chain* chainp = static_cast<Chain*>(&that); // is &that correct?
    
    if (active() == &that) {
        exit();
    } else {
        Secure secure;
        queue.remove(chainp);
    }
}

void Scheduler::resume() {
    // TODO: Secure?
    if (active() != nullptr) {
        Entrant* e = static_cast<Entrant*>(active());
        Chain* c = static_cast<Chain*>(e);
        queue.enqueue(c);
    }
    schedule();
}

Scheduler scheduler;