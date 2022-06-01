
#ifndef __TASK2_H__
#define __TASK2_H__

#include "device/cgastr.h"
#include "user/appl.h"

class Task2 : public Application {
   public:
    Task2();

    void action();
};

extern Task2 task2;

#endif