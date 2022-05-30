
#include "task1.h"
#include "task2.h"

char stack1[65536];

Task1::Task1() : Coroutine{stack1 + sizeof(stack1)} {}

void Task1::action() {
    while (true) {
        kout << "task 1" << endl;
        resume(task2);
    }
}

Task1 task1{};