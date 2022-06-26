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
#include "meeting/semaphore.h"
 
class Keyboard : public Gate {
private:
	Keyboard(const Keyboard &copy); // prevent copying

	Keyboard_Controller ctrl;

	Key latest_key;
	Semaphore key_semaphore;
	bool latest_key_valid; 
 
public:
	Keyboard();
 
	// PLUGIN: "Plugs in" the keyboard (driver). From now on, keypresses are handled.
	void plugin();

	bool prologue();
	void epilogue();
	Key getkey();
};

extern Keyboard keyboard;

#endif
