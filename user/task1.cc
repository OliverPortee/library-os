
#include "task1.h"
#include "thread/scheduler.h"

char stack1[65536];

Task1::Task1() : Application{stack1 + sizeof(stack1)} {}

void Task1::action() {
    while (true) {
        kout << "task 1" << endl;
        scheduler.resume();
    }
}

Task1 task1{};