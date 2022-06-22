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
#include "syscall/guarded_organizer.h"
#include "user/task1.h"
#include "user/task2.h"

Keyboard::Keyboard() : ctrl{}, latest_key{}, key_semaphore{0}, signaled{false} {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::slots::keyboard, *this);
    pic.allow(PIC::devices::keyboard);
}

bool Keyboard::prologue() {
    latest_key = ctrl.key_hit();
    if (latest_key.valid()) {
        // set key_semaphore count to 1
        if (!signaled) {
            key_semaphore.signal();
            signaled = true;
        }

        if (latest_key.ctrl() && latest_key.alt() && latest_key.scancode() == Key::scan::del) {
            ctrl.reboot();
        }
        char character = (char)latest_key;
        if (character == '1') {
            organizer.Organizer::kill(task1);
        } else if (character == '2') {
            organizer.Organizer::kill(task2);
        }
        return true;
    }

    // wait() should not block if signaled is true
    if (signaled) {
        key_semaphore.wait();
        signaled = false;
    }

    return false;
}

void Keyboard::epilogue() {
    // TODO: are these two lines save since they are not atomic?
    kout << (char)latest_key << flush;
}

Key Keyboard::getkey() {
    key_semaphore.wait();
    // what if an interrupt changes latest_key to an invalid key here
    Key key = latest_key;
    // key should still be valid and usable by other applications
    // again, what if an interrupt changes latest_key to an invalid key here
    key_semaphore.signal();
    return key;
}

Keyboard keyboard{};