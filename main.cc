#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"
#include "machine/vgascr.h"

extern "C" {
    void read_ebx(int* out);
}

int main() {
    // get multiboot2 info address from ebx register
    int ebx;
    read_ebx(&ebx);

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
