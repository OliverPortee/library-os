/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstracts an interrupt vector table. Allows to configure handler routines */
/* for every hardware and software interrupt and every CPU exception.        */
/*****************************************************************************/

#include "plugbox.h"
#include "device/panic.h"

Plugbox::Plugbox() {
    for (unsigned int i = 0; i < num_gates; ++i) {
        gates[i] = &panic;
    }
}

void Plugbox::assign(unsigned int slot, Gate& gate) {
    if (slot < num_gates) {
        gates[slot] = &gate;
    }
}

Gate& Plugbox::report(unsigned int slot) {
    return *gates[slot];
}

Plugbox plugbox{};