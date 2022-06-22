/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The class Semaphore implements the synchronization concept of the         */
/* counting semaphore.                                                       */
/*****************************************************************************/

/* Add your code here */ 
#include "meeting/semaphore.h"
#include "thread/organizer.h"
#include "meeting/waitingroom.h"

Semaphore::Semaphore(int c) : cur_count{c}, max_count{c} {}

void Semaphore::p() {
    if (cur_count > 0) {
        cur_count--;
        return;
    } else {
        // block active process
        organizer.block(organizer.active(), *this);
    }
}

void Semaphore::v() {
    if (cur_count == 0) {
        // dequeue first process and wake it up
        Chain* chainp = dequeue();
        if (chainp) {
            auto* customer = static_cast<Customer*>(chainp);
            organizer.wakeup(*customer);
            return;
        }
    }
    
    if (cur_count < max_count) cur_count++;
}

inline void Semaphore::wait() {
    p();
}

inline void Semaphore::signal() {
    v();
}