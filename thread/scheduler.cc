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

#include "device/cgastr.h"
#include "guard/secure.h"

char stack[16384];

Scheduler::Scheduler() : loop{stack + sizeof(stack)} {}

void Scheduler::ready(Entrant& that) { queue.enqueue(&that); }

void Scheduler::schedule() {
    Chain* chain = queue.dequeue();
    Coroutine* coroutine;
    if (chain == nullptr) {
        coroutine = static_cast<Coroutine*>(&loop);
    } else {
        Entrant* e = static_cast<Entrant*>(chain);
        coroutine = static_cast<Coroutine*>(e);
    }

    if (active() == nullptr) {
        go(*coroutine);
    } else {
        dispatch(*coroutine);
    }
}

void Scheduler::exit() { schedule(); }

void Scheduler::kill(Entrant& that) {
    if (active() == &that) {
        exit();
    } else {
        Chain* chain = static_cast<Chain*>(&that);
        queue.remove(chain);
    }
}

void Scheduler::resume() {
    if (active() != nullptr && active() != &loop) {
        Entrant* e = static_cast<Entrant*>(active());
        Chain* c = static_cast<Chain*>(e);
        queue.enqueue(c);
    }
    schedule();
}