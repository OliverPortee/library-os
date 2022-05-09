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

#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"

Keyboard::Keyboard() : ctrl{}, character{-1} {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::slots::keyboard, *this);
    pic.allow(PIC::devices::keyboard);
}

bool Keyboard::prologue() {
    Key key = ctrl.key_hit();
    if (key.valid()) {
        if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del) {
            ctrl.reboot();
        }
        character = (char)key;
        return true;
    } else {
        character = -1;
    }
    return false;
}

void Keyboard::epilogue() {
    kout << character << flush;
    character = -1;
}

Keyboard keyboard{};