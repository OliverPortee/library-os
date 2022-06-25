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
#include "device/cgastr.h"
#include "syscall/guarded_organizer.h"
#include "object/assert.h"

Watch::Watch(int us) : PIT(us), ticks_per_ms{1000 / us} {
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
    organizer.Organizer::resume();
}

Watch watch{static_cast<int>(0.838*65536)};