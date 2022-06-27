
#include "syscall/thread.h"

class Idle : public Thread {
   public:
    Idle(void* tos) : Thread{tos} {}

    void action() {
        // TODO!
        while (true) {}
    }
};