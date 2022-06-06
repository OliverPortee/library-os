/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Handles timer interrupts by managing a time slice and triggering a        */
/* process switch if necessary.                                              */
/*****************************************************************************/

#ifndef __watch_include__
#define __watch_include__

/* INCLUDES */

#include "guard/gate.h"
#include "machine/pit.h"

class Watch : public Gate, public PIT {
private:
	Watch(const Watch &copy); // prevent copying
public:
	// WATCH: Timer initialization, see PIT.
	Watch(int us) : PIT(us) {}

	// WINDUP: "Winds up" the clock. To do this, the watch object must register
	//         with the Plugbox plugbox and allow the interrupts of the timer
	//         module with the help of the global pic object. 
	void windup();

	// PROLOGUE: Contains the prologue of the interrupt handler.
	bool prologue();

	// EPILOGUE: This method triggers the process switch.
	void epilogue();
};

#endif
