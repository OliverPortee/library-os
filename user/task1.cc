
#include "task1.h"

#include "device/cgastr.h"

char stack1[65536];

Task1::Task1() : Thread{stack1 + sizeof(stack1)} {}

void Task1::action() {
    unsigned int i = 0;
    while (true) {
        kout << "task 1: " << i++ << endl;
    }
}

Task1 task1{};