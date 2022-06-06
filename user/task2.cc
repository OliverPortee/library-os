
#include "task2.h"

#include "device/cgastr.h"

char stack2[65536];

Task2::Task2() : Thread{stack2 + sizeof(stack2)} {}

void Task2::action() {
    unsigned int i = 0;
    while (true) {
        kout << "task 2: " << i++ << endl;
    }
}

Task2 task2{};