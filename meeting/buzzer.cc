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
#include "object/assert.h"


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
    assert(ms > 0, "Buzzer::set with ms <= 0");
    bellringer.job(this, watch.ticks_per_ms * ms);
}

void Buzzer::sleep() {
    auto current = static_cast<Customer*>(organizer.active());
    organizer.Organizer::block(*current, *this);
}