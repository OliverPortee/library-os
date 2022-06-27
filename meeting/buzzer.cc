/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* An "alarm clock" is a synchronization object that allows one or more      */
/* threads to put themselves to sleep for a specified time.                  */
/*****************************************************************************/

#include "meeting/buzzer.h"
#include "syscall/guarded_organizer.h"
#include "device/watch.h"
#include "thread/customer.h"
#include "meeting/bellringer.h"


Buzzer::~Buzzer() {
    bellringer.cancel(this);
}

void Buzzer::ring() {
    while (Chain* chain = dequeue()) {
        auto customer = static_cast<Customer*>(chain);
        organizer.Organizer::wakeup(*customer);
    }
}

void Buzzer::set(int ms) {
    bellringer.job(this, watch.ticks_per_ms);
}

void Buzzer::sleep() {
    organizer.Organizer::resume();
}