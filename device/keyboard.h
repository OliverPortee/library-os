/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"
 
class Keyboard : public Gate {
private:
	Keyboard(const Keyboard &copy); // prevent copying
/* Add your code here */ 
 
public:
	Keyboard();
 
	// PLUGIN: "Plugs in" the keyboard (driver). From now on, keypresses are handled.
	void plugin();

	void trigger();
};

extern Keyboard keyboard;

#endif
