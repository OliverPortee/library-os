
#include "task1.h"
#include "task2.h"
#include "thread/scheduler.h"

char stack2[65536];

Task2::Task2() : Entrant{stack2 + sizeof(stack2)} {}

void Task2::action() {
    int i = 0;

    while (true) {
        kout << "task 2: " << i++ << endl;

        // kill task 1 after printing 5 times
        if (i == 5) {
            scheduler.kill(task1);
        }
 
        // kill this task after printing 10 times
        if (i < 10) {
            scheduler.resume();
        } else {
            scheduler.kill(task2);
            scheduler.resume();
        }
    }
}

Task2 task2{};