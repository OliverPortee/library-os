
#include "task1.h"
#include "thread/scheduler.h"

char stack1[65536];

Task1::Task1() : Entrant{stack1 + sizeof(stack1)} {}

void Task1::action() {
    int i = 0;
    while (true) {
        kout << "task 1: " << i++ << endl;
        scheduler.resume();
    }
}

Task1 task1{};