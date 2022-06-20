/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements a list of processes (Customer objects) that are all waiting    */
/* for a specific event.                                                     */
/*****************************************************************************/

#include "meeting/waitingroom.h"

#include "thread/organizer.h"

Waitingroom::Waitingroom() {}

Waitingroom::~Waitingroom() {
    while (Chain* chain = dequeue()) {
        auto* customer = static_cast<Customer*>(chain);
        organizer.wakeup(*customer);
    }
}

void Waitingroom::remove(Customer* customer) {
    auto* chain = static_cast<Chain*>(customer);
    Queue::remove(chain);
}