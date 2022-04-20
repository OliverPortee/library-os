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

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "guard/gate.h"

const unsigned int timer = 32;
const unsigned int keyboard = 33;

class Plugbox {
private:
	Plugbox(const Plugbox &copy); // prevent copying
public:
	Plugbox();
	void assign(unsigned int slot, Gate& gate);
	Gate& report(unsigned int slot);
};

#endif
