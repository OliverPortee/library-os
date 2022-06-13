/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "machine/pit.h"
 #include "object/assert.h"

PIT::PIT(int us) { interval(us); }

int PIT::interval() const { return us; }

void PIT::interval(int us) {
    assert(us >= 1, "PIT::interval called with < 1 us");
    const unsigned int counter = us / 0.838;
    //  00 – selects counter 0
    //  11 – read both lower order and higher order bytes
    // 010 – periodic interrupts
    //   0 – binary counting
    const unsigned char ctrl_byte = 0b00110100;
    port.outb(ctrl_byte);
    port.outb(counter & 0xff); // lower order
    port.outb(counter >> 8); // higher order
    this->us = us;
}