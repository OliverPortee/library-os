
#include "task1.h"

#include "device/cgastr.h"
#include "syscall/guarded_buzzer.h"
#include "syscall/guarded_organizer.h"
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_keyboard.h"

char stack1[65536];

Task1::Task1() : Thread{stack1 + sizeof(stack1)} {}

Guarded_Semaphore sem{1};

void Task1::action() {
    sem.wait();
    for (unsigned int i = 0; i < 5; ++i) {
        kout << "task 1: " << i << endl;
        organizer.resume();
    }
    sem.signal();

    Guarded_Buzzer buzzer;
    while (true) {
        sem.wait();
        kout << endl << "press any key to sleep 1s: " << flush;
        keyboard.getkey();
        kout << endl << "going to sleep..." << endl;

        buzzer.set(1000);
        buzzer.sleep();
        kout << "wake up" << endl;
        sem.signal();
    }
}

Task1 task1{};