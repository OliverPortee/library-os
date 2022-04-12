#include "machine/cgascr.h"
#include "machine/keyctrl.h"

int main()
{

	CGA_Screen screen{};
	Keyboard_Controller ctrl{};
	ctrl.set_repeat_rate(5, 3);
	ctrl.set_led(Keyboard_Controller::led::caps_lock, true);
	ctrl.set_led(Keyboard_Controller::led::num_lock, true);
	screen.print("done", 4, 0x0f);
	while (true) {
		Key key = ctrl.key_hit();
		if (key.valid()) {
			char c = (char) key;
			screen.print(&c, 1, 0x0f);
		}
	}

	return 0;
}
