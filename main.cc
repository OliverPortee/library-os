#include "machine/cpu.h"
#include "device/keyboard.h"

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	while (true) {}

	return 0;
}
