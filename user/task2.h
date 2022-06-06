
#ifndef __TASK2_H__
#define __TASK2_H__

#include "syscall/thread.h"

class Task2 : public Thread {
   public:
    Task2();

    void action();
};

extern Task2 task2;

#endif