/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       K E Y B O A R D _ C O N T R O L L E R               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The PC's keyboard controller.                                             */
/*****************************************************************************/

/* INCLUDES */

#include "machine/keyctrl.h"
 
/* STATIC MEMBERS */

unsigned char Keyboard_Controller::normal_tab[] = {
    0,   0,   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 225, 39,   '\b',
    0,   'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 129, '+', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 148, 132, '^', 0,   '#',  'y',
    'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0,   '*', 0,   ' ', 0,    0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    '-',
    0,   0,   0,   '+', 0,   0,   0,   0,   0,   0,   0,   '<', 0,   0};

unsigned char Keyboard_Controller::shift_tab[] = {
    0,   0,   '!', '"', 21,  '$', '%', '&', '/', '(', ')', '=', '?', 96, 0,
    0,   'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 154, '*', 0,  0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 153, 142, 248, 0,   39, 'Y',
    'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,   0,   0,   ' ', 0,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   '>', 0,   0};

unsigned char Keyboard_Controller::alt_tab[] = {
    0, 0, 0, 253, 0, 0, 0, 0, '{', '[', ']', '}', '\\', 0, 0,   0, '@', 0,
    0, 0, 0, 0,   0, 0, 0, 0, 0,   '~', 0,   0,   0,    0, 0,   0, 0,   0,
    0, 0, 0, 0,   0, 0, 0, 0, 0,   0,   0,   0,   0,    0, 230, 0, 0,   0,
    0, 0, 0, 0,   0, 0, 0, 0, 0,   0,   0,   0,   0,    0, 0,   0, 0,   0,
    0, 0, 0, 0,   0, 0, 0, 0, 0,   0,   0,   0,   0,    0, '|', 0, 0};

unsigned char Keyboard_Controller::asc_num_tab[] = {
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', ','};
unsigned char Keyboard_Controller::scan_num_tab[] = {
    8,  9, 10, 53, 5,  6, 7, 27, 2, 3,  4,  11, 51};

/* PRIVATE METHODS */

// KEY_DECODED: Interprets the keyboard's make and break codes and
//              provides the ASCII code, the scan code, and information
//              which additional keys (like SHIFT or CTRL) were pressed.
//              Return value true means that the key is complete;
//              otherwise, some make or break code(s) are still missing.
bool Keyboard_Controller::key_decoded()
{
	bool done = false;

	// The keys that were added in MF II keyboards -- compared to the older
	// AT keyboard -- always send one of two possible prefix bytes first.
	if (code == prefix1 || code == prefix2) {
		prefix = code;
		return false;
	}

	// Releasing a key is actually only interesting in this implementation
	// for the "modifier" keys SHIFT, CTRL and ALT.  For the other keys, we
	// can ignore the break code.
	if (code & break_bit) {
		code &= ~break_bit; // A key's break code is identical to its
				    // make code with the break_bit set.
		switch (code) {
		case 42:
		case 54:
			gather.shift (false); break;
		case 56:
			if (prefix == prefix1)
				gather.alt_right(false);
			else
				gather.alt_left(false);
			break;
		case 29:
			if (prefix == prefix1)
				gather.ctrl_right(false);
			else
				gather.ctrl_left(false);
			break;
		}

		// A prefix is only valid for the directly succeessive code.  So
		// it can be discarded now.
		prefix = 0;

		// This implementation doesn't do anything with break codes, so
		// return false here.
		return false;
	}

	// A key was pressed. If it was a modifier key (SHIFT, ALT, NUM_LOCK
	// etc.), only internal state changes. By returning 'false' we signal
	// that the keyboard input hasn't finished yet. For all other keys we
	// store ASCII and scan code and return 'true' to signal a successful
	// keyboard input, although the break code is still missing.

	switch (code) {
	case 42:
	case 54:
		gather.shift (true); break;
	case 56:
		if (prefix == prefix1)
			gather.alt_right(true);
		else
			gather.alt_left(true);
		break;
	case 29:
		if (prefix == prefix1)
			gather.ctrl_right(true);
		else
			gather.ctrl_left(true);
		break;
	case 58:
		gather.caps_lock(!gather.caps_lock());
		set_led(led::caps_lock, gather.caps_lock());
		break;
	case 70:
		gather.scroll_lock(!gather.scroll_lock());
		set_led(led::scroll_lock, gather.scroll_lock());
		break;
	case 69:                        // Num Lock or Pause?
		if (gather.ctrl_left()) // pause key
		{
			// On old keyboards, Pause could only be triggered via
			// CTRL+NumLock. That's why "modern" MF II keyboards
			// still send this code combination when Pause was
			// pressed. The Pause key usually doesn't yield an ASCII
			// code, but checking our tables doesn't hurt. Either
			// way the key is complete now.
			get_ascii_code();
			done = true;
		} else // NumLock
		{
			gather.num_lock(!gather.num_lock());
			set_led(led::num_lock, gather.num_lock());
		}
		break;

	default: // all other keys
		// retrieve ASCII code from the respective table, done
		get_ascii_code();
		done = true;
	}

	// A prefix is only valid for the directly succeessive code.  So it
	// can be discarded now.
	prefix = 0;

	if (done) // keyboard input finished?
		return true;
	else
		return false;
}

// GET_ASCII_CODE: uses decoding tables to determine the key's ASCII
//                 code from the scan code and set modifier bits.

void Keyboard_Controller::get_ascii_code()
{
	// Special case scan code 53: This code is sent both by the 'minus' key
	// of the regular keyboard area and the 'division' key of the number
	// block. In order to find the correct code matching what's printed on
	// the key, we have to translate the code in case it's the number block.
	if (code == 53 && prefix == prefix1) // 'division' key (number block)
	{
		gather.ascii('/');
		gather.scancode(Key::scan::div);
	}

	// Using the modifier bit we need to select the correct table. For
	// simplicity's sake we grant Num Lock precedence over ALT, SHIFT
	// and Caps Lock. CTRL doesn't have its own table.

	else if (gather.num_lock() && !prefix && code >= 71 && code <= 83) {
		// When Num Lock is enabled and one of the number block's keys
		// is pressed (codes 71-83), we want to emit ASCII and scan
		// codes of the digit keys instead of the cursor keys. Of
		// course, the cursor-block keys still should be usable for
		// cursor control. They additionally send a SHIFT, but we ignore
		// that here.
		gather.ascii(asc_num_tab[code - 71]);
		gather.scancode(scan_num_tab[code - 71]);
	} else if (gather.alt_right()) {
		gather.ascii(alt_tab[code]);
		gather.scancode(code);
	 }
      else if (gather.shift ())
	 {
		gather.ascii(shift_tab[code]);
		gather.scancode(code);
	 }
      else if (gather.caps_lock ())
	 {  // Caps Lock should only have an effect on letters
		if ((code >= 16 && code <= 26) || (code >= 30 && code <= 40) ||
		    (code >= 44 && code <= 50)) {
			gather.ascii(shift_tab[code]);
			gather.scancode(code);
		} else {
			gather.ascii(normal_tab[code]);
			gather.scancode(code);
		}
	 }
      else
	 {
		gather.ascii(normal_tab[code]);
		gather.scancode(code);
	 }
}

/* PUBLIC METHODS */

// KEYBOARD_CONTROLLER: keyboard initialization: disables all LEDs and
//                      sets the repeat rate to maximum.

Keyboard_Controller::Keyboard_Controller() : ctrl_port(0x64), data_port(0x60)
{
	// disable all LEDs (many PCs enable Num Lock during the boot process)
	set_led(led::caps_lock, false);
	set_led(led::scroll_lock, false);
	set_led(led::num_lock, false);

	// maximum speed, minimal delay
	set_repeat_rate(0, 0);
}

// KEY_HIT: Meant for retrieving information from the keyboard after a
//          keyboard interrupt occurred. If the key-pressing event has
//          concluded and a scan code and -- if applicable -- an ASCII
//          code could be determined, these are returned in a Key object.
//          Otherwise, key_hit () returns an invalid value, which can be
//          checked by calling Key::valid ().

Key Keyboard_Controller::key_hit ()
{
	int status = ctrl_port.inb();
	if ((status & outb) == 0 || (status & auxb) != 0) {
		// if there is no output available or event comes from mouse
		return Key{}; // return invalid key
	}
	code = data_port.inb();
	if (!key_decoded()) {
		return Key{}; // return invalid key
	}
	return gather;
}

// REBOOT: Reboots the PC. Yes, in a PC the keyboard controller is
//         responsible for this.

void Keyboard_Controller::reboot()
{
	int status;

	// Tell the BIOS that this reset is intentional and no memory test has
	// to be run.

	*(unsigned short *)0x472 = 0x1234;

	// keyboard controller triggers the reset
	do {
		status =
		    ctrl_port.inb(); // wait until last command is processed
	} while ((status & inpb) != 0);
	ctrl_port.outb(cpu_reset); // reset
}

unsigned char map_speed(int speed) {

	switch (speed) {
	case 30:
		return 0x00;
	case 25:
		return 0x02;
	case 20:
		return 0x04;
	case 15:
		return 0x08;
	case 10:
		return 0x0c;
	case 7:
		return 0x10;
	case 5:
		return 0x14;
	default:
	// TODO: Is that right? Case 31 for 2 characters per second?
		return 0x00;
	}
}

// SET_REPEAT_RATE: Function for setting the keyboard repeat rate. The
//                  delay paraemter determines how long a key has to be
//                  pressed until automatic repetition starts. Accepted
//                  values are between 0 (minimal waiting time) and 3
//                  (maximal waiting time). speed determins how fast the
//                  key codes should come in during the repetition phase.
//                  Allowed values are between 0 (very fast) and 31 (very
//                  slow).

void Keyboard_Controller::set_repeat_rate (int speed, int delay)
{
	if (delay > 3) {
		delay = 3;
	}
	if (delay < 0) {
		delay = 0;
	}
	int status;
	do {
		status = ctrl_port.inb();
	} while ((status & inpb) != 0);
	data_port.outb(kbd_cmd::set_speed);
	do {
		status = ctrl_port.inb();
	} while ((status & outb) == 0 || data_port.inb() != kbd_reply::ack);
	data_port.outb(map_speed(speed) | (((unsigned char) delay) << 5));
	do {
		status = ctrl_port.inb();
	} while ((status & outb) == 0 || data_port.inb() != kbd_reply::ack);
}

// SET_LED: sets or clears the specified LED

void Keyboard_Controller::set_led (char led, bool on)
{
	int status;
	do {
		status = ctrl_port.inb();
	} while ((status & inpb) != 0);
	data_port.outb(kbd_cmd::set_led);
	do {
		status = ctrl_port.inb();
	} while ((status & outb) == 0 || data_port.inb() != kbd_reply::ack);
	leds = (leds & ~led) | (on ? (0xff & led) : 0);
	data_port.outb(leds);
	do {
		status = ctrl_port.inb();
	} while ((status & outb) == 0 || data_port.inb() != kbd_reply::ack);
}
