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

#include "guard/secure.h"
#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/plugbox.h"
#include "syscall/guarded_organizer.h"
#include "user/task1.h"
#include "user/task2.h"

Keyboard::Keyboard() : ctrl{}, last_key{}, last_valid_key{}, key_semaphore{0} {}

void Keyboard::plugin() {
    plugbox.assign(Plugbox::slots::keyboard, *this);
    pic.allow(PIC::devices::keyboard);
}

bool Keyboard::prologue() {
    last_key = ctrl.key_hit();

    if (last_key.valid()) {
        if (!last_key.valid()) {
            key_semaphore.signal();
        }   

        if (last_key.ctrl() && last_key.alt() && last_key.scancode() == Key::scan::del) {
            ctrl.reboot();
        }
        char character = (char)last_key;
        if (character == '1') {
            organizer.Organizer::kill(task1);
        } else if (character == '2') {
            organizer.Organizer::kill(task2);
        }
        return true;
    }

    return false;
}

void Keyboard::epilogue() {
    if (last_key.valid()) {
        if (!last_valid_key.valid()) key_semaphore.signal();    // signal only if earlier key was invalidated by getkey()
        last_valid_key = last_key;                              
    } 
        
    kout << (char)last_key << flush;
}

Key Keyboard::getkey() {
    key_semaphore.wait();
    Key key = last_valid_key;
    last_valid_key.invalidate();    // mark key as used, meaning that some thread completed wait()
                                    // and the semaphore count is now 0 again
    return key;
}
