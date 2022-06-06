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
#include "thread/scheduler.h"

Watch::Watch(int us) : PIT(us) {}

void Watch::windup() {
    plugbox.assign(Plugbox::slots::timer, *this);
    pic.allow(PIC::devices::timer);
}

bool Watch::prologue() {
    return true;
}

void Watch::epilogue() {
    scheduler.resume();
}

Watch watch{static_cast<int>(0.838*65536)};