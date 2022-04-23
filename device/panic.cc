/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Default interrupt handler.                                                */
/*****************************************************************************/

#include "device/panic.h"
#include "device/cgastr.h"
#include "machine/cpu.h"

void Panic::trigger() {
    kout << "ERROR!" << endl;
    cpu.halt();
}

Panic panic{};
