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

#ifndef __pic_include__
#define __pic_include__

#include "guard/gate.h"
#include "machine/io_port.h"

class PIC {
private:
	PIC(const PIC &copy); // prevent copying

	IO_Port port1;
	IO_Port port2;
	unsigned char disabled_interrupts;

public:
	PIC() : port1{0x21}, port2{0xa1}, disabled_interrupts{0xff} {}

	enum devices {
		timer = 0,
		keyboard = 1
	};

	void allow(int interrupt_device);

	void forbid(int interrupt_device);

	bool is_masked(int interrupt_device);
};

extern PIC pic;

#endif
