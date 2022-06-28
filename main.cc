#include "syscall/guarded_keyboard.h"
#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"

int main() {
    Secure secure;
    cpu.enable_int();
    guarded_keyboard.plugin();
    watch.windup();

    organizer.Organizer::ready(app);
    organizer.Scheduler::schedule();

    return 0;
}
