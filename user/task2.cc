
#include "task2.h"

#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_keyboard.h"

char stack2[65536];

extern Guarded_Semaphore sem;

Task2::Task2() : Thread{stack2 + sizeof(stack2)} {}

void Task2::action() {
    sem.wait();
    for (unsigned int i = 0; i < 5; ++i) {
        kout << "task 2: " << i << endl;
        organizer.resume();
    }
    sem.signal();
    while (true) {
        kout << "waiting for keyboard input: " << endl;
        Key k = keyboard.getkey();
        kout << endl << "key was: " << (char) k << endl;
    }    
}

Task2 task2{};