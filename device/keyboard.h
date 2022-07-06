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

	Key last_key;
	Key last_valid_key;
	Semaphore key_semaphore;
 
public:
	Keyboard();
 
	// PLUGIN: "Plugs in" the keyboard (driver). From now on, keypresses are handled.
	void plugin();

	bool prologue();
	void epilogue();
	Key getkey();
};

#endif
