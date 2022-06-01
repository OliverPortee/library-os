
#ifndef __TASK1_H__
#define __TASK1_H__

#include "device/cgastr.h"
#include "user/appl.h"

class Task1 : public Application {
   public:
    Task1();

    void action();
};

extern Task1 task1;

#endif