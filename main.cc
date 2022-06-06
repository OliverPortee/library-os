#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "syscall/guarded_scheduler.h"
#include "user/appl.h"

int main() {
    Secure secure;
    cpu.enable_int();
    keyboard.plugin();
    watch.windup();

    scheduler.Scheduler::ready(app);
    scheduler.Scheduler::schedule();

    return 0;
}
