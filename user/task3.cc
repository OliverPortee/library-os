
#include "task3.h"

#include "device/cgastr.h"
#include "syscall/guarded_keyboard.h"
#include "machine/key.h"

extern Guarded_Keyboard guarded_keyboard;

char stack3[65536];

Task3::Task3() : Thread{stack3 + sizeof(stack3)} {}

void Task3::action() {
    kout << "wait for keyboard input: " << endl;
    Key k = guarded_keyboard.getkey();
    kout << "key was: " << k.valid() << endl;    
}

Task3 task3{};