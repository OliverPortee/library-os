#include "machine/cgascr.h"
#include "machine/keyctrl.h"

int main()
{

	CGA_Screen screen{};
	Keyboard_Controller ctrl{};
	ctrl.set_repeat_rate(5, 0);
	ctrl.set_led(Keyboard_Controller::led::caps_lock, true);
	ctrl.set_led(Keyboard_Controller::led::num_lock, true);
	screen.print("done", 4, 0x0f);
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
			screen.print(&c, 1, 0x0f);
				break;
			}
		}
	}

	return 0;
}
