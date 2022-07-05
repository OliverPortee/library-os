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
    scr.fill((char) 155);
    return 0;
}
