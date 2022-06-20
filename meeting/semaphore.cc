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
Semaphore::Semaphore(int c) : count{c}

void Semaphore::p() {
    if (count > 0) {
        count--;
        return;
    } else {
        // block active process
    }
}

void Semaphore::v() {
    if (count == 0) // wake up first process in waiting list, return;
    count++;
}

inline void Semaphore::wait() {
    p();
}

inline void Semaphore::signal() {
    v();
}