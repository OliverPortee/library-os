
#include "task2.h"

#include "task1.h"

char stack2[65536];

Task2::Task2() : Coroutine{stack2 + sizeof(stack2)} {}

void Task2::action() {
    while (true) {
        kout << "task 2" << endl;
        resume(task1);
    }
}

Task2 task2{};