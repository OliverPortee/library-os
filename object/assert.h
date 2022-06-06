
#ifndef __assert_h__
#define __assert_h__

#include "machine/cpu.h"
#include "device/cgastr.h"

inline void assert(bool b, char* message) {
    if (!b) {
        kout << message << endl;
        cpu.halt();
    }
}

#endif