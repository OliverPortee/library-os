#include "machine/cpu.h"
#include "device/keyboard.h"
#include "user/appl.h"

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	Application app{};
	app.action();

	return 0;
}
