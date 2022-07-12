#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "library/random.h"
#include "machine/cpu.h"
#include "machine/vgascr.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"
#include "user/raytracer/rt_app.h"

void test_scr() {
    // step through with gdb
    for (unsigned char i = 0; i < 5; i++) {
        vga_scr.fill(i);
        // 0: black
        // 1: blue
        // 2: green
        // 3: cyan
        // 4: red
    }

    struct byte_colour light_blue {
        0x00, 0x1c, 0x71
    };
    vga_scr.fill(vga_scr.match_colour(light_blue));
}

int main() {
    Secure secure;
    cpu.enable_int();
    keyboard.plugin();
    // watch.windup();

    raytracer.set_scene(Scene::secret);

    organizer.Organizer::ready(raytracer);
    organizer.Scheduler::schedule();

    // test_scr();
    return 0;
}