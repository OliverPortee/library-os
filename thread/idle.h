
#include "syscall/thread.h"
#include "machine/cpu.h"

class Idle : public Thread {
   public:
    Idle(void* tos) : Thread{tos} {}

    void action() {
        while (true) {
            cpu.idle();
        }
    }
};