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

Keyboard::Keyboard() : ctrl{}, latest_key{}, key_semaphore{1} {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::slots::keyboard, *this);
    pic.allow(PIC::devices::keyboard);
}

bool Keyboard::prologue() {
    latest_key = ctrl.key_hit();
    if (latest_key.valid()) {
        key_semaphore.signal();
        if (latest_key.ctrl() && latest_key.alt() && latest_key.scancode() == Key::scan::del) {
            ctrl.reboot();
        }
        char character = (char)latest_key;
        if (character == '1') {
            scheduler.Scheduler::kill(task1);
        } else if (character == '2') {
            scheduler.Scheduler::kill(task2);
        }
        return true;
    }
    return false;
}

void Keyboard::epilogue() {
    // TODO: are these two lines save since they are not atomic?
    kout << (char)latest_key << flush;
}

Key Keyboard::getkey() {
    // wait if there is no valid key currently

    if (latest_key.valid()) return latest_key;
    key_semaphore.wait();
    // what if an interrupt changes latest_key to an invalid key
    return latest_key;
}

Keyboard keyboard{};