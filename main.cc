#include "device/cgastr.h"
#include "machine/cgascr.h"
#include "object/o_stream.h"
#include "machine/keyctrl.h"

int main()
{

	kout << (void *)0xff77 << endl;
	kout << 0 << endl;
	
	kout << "short: " << (short) -32768 << endl;
	kout << "short: " << (short)  32767 << endl;
	kout << "unsigned short: " << (unsigned short) 65535 << endl;
	kout << "int: " << (int) -2147483648 << endl;
	kout << "int: " << (int)  2147483647 << endl;
	kout << "unsigned int: " << (unsigned int) 4294967295 << endl;
	kout << "long: " << (long) -9223372036854775808 << endl;
	kout << "long: " << (long)  9223372036854775807 << endl;
	kout << "unsigned long: " << (unsigned long) 18446744073709551615 << endl;

	kout << hex;

	kout << 0 << endl;
	kout << "short: " << (short) -32768 << endl;
	kout << "short: " << (short)  32767 << endl;
	kout << "unsigned short: " << (unsigned short) 65535 << endl;
	kout << "int: " << (int) -2147483648 << endl;
	kout << "int: " << (int)  2147483647 << endl;
	kout << "unsigned int: " << (unsigned int) 4294967295 << endl;
	kout << "long: " << (long) -9223372036854775808 << endl;
	kout << "long: " << (long)  9223372036854775807 << endl;
	kout << "unsigned long: " << (unsigned long) 18446744073709551615 << endl;

	Keyboard_Controller ctrl{};
	ctrl.set_repeat_rate(5, 0);
	
	while (true) {
		Key key = ctrl.key_hit();
		if (key.valid()) {
			char c = (char) key;
			switch (c)
			{
			case '0':
				ctrl.set_repeat_rate(5, 0);
				break;
			case '1':
				ctrl.set_repeat_rate(5, 1);
				break;
			case '2':
				ctrl.set_repeat_rate(5, 2);
				break;
			case '3':
				ctrl.set_repeat_rate(5, 3);
				break;
			case '4':
				ctrl.set_led(Keyboard_Controller::led::num_lock, true);
				break;
			case '5':
				ctrl.set_led(Keyboard_Controller::led::num_lock, false);
				break;
			default:
			kout.print(&c, 1, 0x0f);
				break;
			}
		}
	}

	return 0;
}
