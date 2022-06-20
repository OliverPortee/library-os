/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements the system-call interface to the Scheduler.                    */
/*****************************************************************************/

#include "syscall/guarded_scheduler.h"
#include "guard/secure.h"

void Guarded_Scheduler::ready(Thread& that) {
    Secure secure;
    Scheduler::ready(that);
}

void Guarded_Scheduler::exit() {
    Secure secure;
    Scheduler::exit();
}

void Guarded_Scheduler::kill(Thread& that) {
    Secure secure;
    Scheduler::kill(that);
}

void Guarded_Scheduler::resume() {
    Secure secure;
    Scheduler::resume();
}

Guarded_Scheduler scheduler{};