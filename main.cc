#include "machine/cpu.h"
#include "device/keyboard.h"
#include "user/appl.h"

extern Application app;

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	app.action();

	return 0;
}
