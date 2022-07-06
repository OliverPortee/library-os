/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Handles timer interrupts by managing a time slice and triggering a        */
/* process switch if necessary.                                              */
/*****************************************************************************/

#include "device/watch.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "syscall/guarded_organizer.h"
#include "object/assert.h"
#include "meeting/bellringer.h"

Watch::Watch(int us, double ticks_per_ms) : PIT(us), ticks_per_ms{ticks_per_ms} {
    assert(us > 0, "watch step us <= 0");
}

void Watch::windup() {
    plugbox.assign(Plugbox::slots::timer, *this);
    pic.allow(PIC::devices::timer);
}

bool Watch::prologue() {
    return true;
}

void Watch::epilogue() {
    bellringer.check();
    organizer.Organizer::resume();
}

Watch watch{10, 0.42}; // TODO: don't hardcode ticks per ms