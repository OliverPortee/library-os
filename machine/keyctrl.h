/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       K E Y B O A R D _ C O N T R O L L E R               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The PC's keyboard controller.                                             */
/*****************************************************************************/

#ifndef __Keyboard_Controller_include__
#define __Keyboard_Controller_include__

#include "machine/io_port.h"
#include "machine/key.h"

class Keyboard_Controller {
private:
	Keyboard_Controller(const Keyboard_Controller &copy); // prevent copying
private:
	unsigned char code;
	unsigned char prefix;
	Key gather;
	char leds;

	// the two used ports of the keyboard controller
	const IO_Port ctrl_port; // status (R) and control register (W)
	const IO_Port data_port; // output (R) and input buffer (W)

	// status-register bits
	enum { outb = 0x01, inpb = 0x02, auxb = 0x20 };

	// commands for the keyboard
	struct kbd_cmd {
		enum { set_led = 0xed, set_speed = 0xf3 };
	};
	enum { cpu_reset = 0xfe };

	// possible answers of the keyboard
	struct kbd_reply {
		enum { ack = 0xfa };
	};

	// constants for keyboard decoding
	enum { break_bit = 0x80, prefix1 = 0xe0, prefix2 = 0xe1 };

	static unsigned char normal_tab[];
	static unsigned char shift_tab[];
	static unsigned char alt_tab[];
	static unsigned char asc_num_tab[];
	static unsigned char scan_num_tab[];

	// KEY_DECODED: Interprets the keyboard's make and break codes and
	//              provides the ASCII code, the scan code, and information
	//              which additional keys (like SHIFT or CTRL) were pressed.
	//              Return value true means that the key is complete;
	//              otherwise, some make or break code(s) are still missing.
	bool key_decoded();

	// GET_ASCII_CODE: uses decoding tables to determine the key's ASCII
	//                 code from the scan code and set modifier bits.
	void get_ascii_code();

public:
	
	// LED names
	struct led {
		enum { caps_lock = 4, num_lock = 2, scroll_lock = 1 };
	};

	// KEYBOARD_CONTROLLER: keyboard initialization: disables all LEDs and
	//                      sets the repeat rate to maximum.
	Keyboard_Controller();

	// KEY_HIT: Meant for retrieving information from the keyboard after a
	//          keyboard interrupt occurred. If the key-pressing event has
	//          concluded and a scan code and -- if applicable -- an ASCII
	//          code could be determined, these are returned in a Key
	//          object. Otherwise, key_hit () returns an invalid value,
	//          which can be checked by calling Key::valid ().
	Key key_hit();

	// REBOOT: Reboots the PC. Yes, in a PC the keyboard controller is
	//         responsible for this.
	void reboot();

	// SET_REPEAT_RATE: Function for setting the keyboard repeat rate. The
	//                  delay paraemter determines how long a key has to be
	//                  pressed until automatic repetition starts. Accepted
	//                  values are between 0 (minimal waiting time) and 3
	//                  (maximal waiting time). speed determins how fast the
	//                  key codes should come in during the repetition
	//                  phase. Allowed values are between 0 (very fast) and
	//                  31 (very slow).
	void set_repeat_rate(int speed, int delay);

	// SET_LED: sets or clears the specified LED
	void set_led(char led, bool on);
};

#endif
