#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"
#include "machine/vgascr.h"

int main() {
    Secure secure;
    cpu.enable_int();
    keyboard.plugin();
    //watch.windup();

    //organizer.Organizer::ready(app);
    //organizer.Scheduler::schedule();
    VGA_Screen scr;

    // step through with gdb
    for (unsigned char i = 0; i < 5; i++)
    {
        scr.fill(i);
        // 0: black
        // 1: blue
        // 2: green
        // 3: cyan
        // 4: red
    }

    // should fill the screen light blue
    scr.fill(scr.match_colour(0x00, 0x1c, 0x71));
            
    return 0;
}
