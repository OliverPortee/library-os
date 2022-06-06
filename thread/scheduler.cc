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

void Scheduler::ready(Entrant& that) { queue.enqueue(&that); }

void Scheduler::schedule() {
    Chain* chain = queue.dequeue();
    if (chain == nullptr) {
        // halt machine if no more tasks to schedule
        cpu.halt();
    }
    Entrant* e = static_cast<Entrant*>(chain);
    Coroutine* coroutine = static_cast<Coroutine*>(e);

    if (active() == nullptr) {
        go(*coroutine);
    } else {
        dispatch(*coroutine);
    }
}

void Scheduler::exit() { schedule(); }

void Scheduler::kill(Entrant& that) {
    Chain* chainp = static_cast<Chain*>(&that);

    if (active() == &that) {
        exit();
    } else {
        queue.remove(chainp);
    }
}

void Scheduler::resume() {
    if (active() != nullptr) {
        Entrant* e = static_cast<Entrant*>(active());
        Chain* c = static_cast<Chain*>(e);
        queue.enqueue(c);
    }
    schedule();
}

Scheduler scheduler;