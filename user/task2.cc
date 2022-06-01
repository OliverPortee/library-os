
#include "task2.h"
#include "thread/scheduler.h"

char stack2[65536];

Task2::Task2() : Application{stack2 + sizeof(stack2)} {}

void Task2::action() {
    int i = 0;

    while (true) {
        kout << "task 2" << endl;
        
        // kill this task after printing 5 times
        i += 1;
        if (i < 5) {
            scheduler.resume();
        } else {
            scheduler.kill(task2);
        }
    }
}

Task2 task2{};