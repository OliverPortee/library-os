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

const unsigned int num_gates = 64;

class Plugbox {
private:
	Plugbox(const Plugbox &copy); // prevent copying
	Gate* gates[num_gates];

public:
	enum slots : unsigned int {
		timer = 32u,
		keyboard = 33u
	};

	Plugbox();
	void assign(unsigned int slot, Gate& gate);
	Gate& report(unsigned int slot);
};

extern Plugbox plugbox;

#endif
