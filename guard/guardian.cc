/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The system's central interrupt handling routine.                          */
/* The parameter specifies the number of the interrupt that occurred.        */
/*****************************************************************************/

/* INCLUDES */
#include "guard/guard.h"
#include "machine/plugbox.h"

/* FUNCTIONS */

extern "C" void guardian(unsigned int slot);

/* GUARDIAN: Low-level interrupt handling. We will extend this function at */
/*           a later point in time.                                        */

void guardian(unsigned int slot) {
    Gate& gate = plugbox.report(slot);
    bool runEpilogue = gate.prologue();
    if (runEpilogue) {
        guard.relay(&gate);
    }
    cpu.enable_int();
}
