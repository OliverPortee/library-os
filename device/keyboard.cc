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
#include "syscall/guarded_scheduler.h"
#include "meeting/semaphore.h"
#include "user/task1.h"
#include "user/task2.h"

Keyboard::Keyboard() : ctrl{}, character{-1}, key_semaphore{1} {}

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
        if (character == '1') {
            scheduler.Scheduler::kill(task1);
        } else if (character == '2') {
            scheduler.Scheduler::kill(task2);
        }
        return true;
    }
    character = -1;
    return false;
}

void Keyboard::epilogue() {
    // TODO: are these two lines save since they are not atomic?
    kout << character << flush;
    character = -1;
}

Key Keyboard::getkey() {
    Key key = ctrl.key_hit();
    if (key.valid()) return key;

    // wait if there is not valid key currently
    key_semaphore.wait();
}

Keyboard keyboard{};