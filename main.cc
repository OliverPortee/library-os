#include "device/cgastr.h"
#include "device/keyboard.h"
#include "machine/cpu.h"
#include "thread/dispatch.h"
#include "thread/scheduler.h"
#include "user/appl.h"
#include "user/task1.h"
#include "user/task2.h"
#include "device/watch.h"
#include "guard/guard.h"

int main() {
    cpu.enable_int();
    keyboard.plugin();

	scheduler.ready(task1);
	scheduler.ready(task2);

	watch.windup();
    while (true) {}

    return 0;
}
