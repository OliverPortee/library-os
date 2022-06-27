
#ifndef __TASK3_H__
#define __TASK3_H__

#include "syscall/thread.h"

class Task3 : public Thread {
   public:
    Task3();
    void action();
};

extern Task3 task3;

#endif