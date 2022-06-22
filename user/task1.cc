
#include "task1.h"

#include "device/cgastr.h"
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_organizer.h"

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
}

Task1 task1{};