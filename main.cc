#include "device/keyboard.h"
#include "device/watch.h"
#include "machine/cpu.h"
#include "syscall/guarded_scheduler.h"
#include "user/appl.h"
#include "user/task1.h"
#include "user/task2.h"

int main() {
    cpu.enable_int();
    keyboard.plugin();

    // TODO: put that into application
    scheduler.ready(task1);
    scheduler.ready(task2);

    watch.windup();

    while (true) {
    }

    return 0;
}
