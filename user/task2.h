
#ifndef __TASK2_H__
#define __TASK2_H__

#include "device/cgastr.h"
#include "thread/coroutine.h"

class Task2 : public Coroutine {
   public:
    Task2();

    void action();
};

extern Task2 task2;

#endif