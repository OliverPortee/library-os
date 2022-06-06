
#include "task2.h"

#include "device/cgastr.h"
#include "guard/secure.h"

char stack2[65536];

Task2::Task2() : Thread{stack2 + sizeof(stack2)} {}

void Task2::action() {
    unsigned int i = 0;
    while (true) {
        Secure secure;
        kout.setpos(0, 10);
        kout << "task 2: " << i++ << endl;
    }
}

Task2 task2{};