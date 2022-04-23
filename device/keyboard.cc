/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#include "keyboard.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "device/cgastr.h"

Keyboard::Keyboard() {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::slots::keyboard, *this);
    pic.allow(PIC::devices::keyboard);
}

void Keyboard::trigger() {
    kout << "keyboard interrupt" << endl;
}
 
Keyboard keyboard{};