#include "device/keyboard.h"
#include "device/watch.h"
#include "machine/cpu.h"
#include "syscall/guarded_scheduler.h"
#include "user/appl.h"

int main() {
    cpu.enable_int();
    keyboard.plugin();

    scheduler.ready(app);
    watch.windup();

    while (true) {}

    return 0;
}
