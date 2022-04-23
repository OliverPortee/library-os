/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* By using the PIC, hardware interrupts can be enabled or suppressed        */
/* individually. This way we can control whether interrupts of a specific    */
/* device are forwarded to the CPU at all. Even then, the interrupt handler  */
/* gets only activated if the CPU is ready to react to interrupts. This can  */
/* be controlled by using class CPU.                                         */
/*****************************************************************************/

#include "pic.h"

void PIC::allow(int interrupt_device) {
    disabled_interrupts = disabled_interrupts & ~(1 << interrupt_device);
    port1.outb(disabled_interrupts);
}

void PIC::forbid(int interrupt_device) {
    disabled_interrupts = disabled_interrupts | (1 << interrupt_device);
    port1.outb(disabled_interrupts);
}

bool PIC::is_masked(int interrupt_device) {
    return (disabled_interrupts & (1 << interrupt_device)) != 0;
}

PIC pic{};