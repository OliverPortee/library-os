
#ifndef __TASK1_H__
#define __TASK1_H__

#include "syscall/thread.h"

class Task1 : public Thread {
   public:
    Task1();

    void action();
};

extern Task1 task1;

#endif