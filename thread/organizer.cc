/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Organizer is a special scheduler that additionally allows processes   */
/* (Customer objects) to wait for events (Waitingroom objects).              */

#include "thread/organizer.h"

#include "object/assert.h"

Organizer::Organizer() {}

void Organizer::block(Customer& customer, Waitingroom& waitingroom) {
    assert(active() == &customer, "Organizer::block on other customer");
    waitingroom.enqueue(&customer);
    customer.waiting_in(&waitingroom);
    exit();
}

void Organizer::wakeup(Customer& customer) {
    Waitingroom* w = customer.waiting_in();
    assert(w != nullptr,
           "Organizer::wakeup called on customer that is not in waitingroom");
    customer.waiting_in(nullptr);
    w->remove(&customer);
    ready(customer);
}

void Organizer::kill(Customer& customer) {
    Waitingroom* w = customer.waiting_in();
    if (w != nullptr) {
        w->remove(&customer);
        customer.waiting_in(nullptr);
    } else {
        Scheduler::kill(customer);
    }
}