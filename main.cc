#include "machine/pic.h"
#include "machine/cpu.h"

int main()
{
	cpu.enable_int();
	pic.allow(PIC::keyboard);

	while (true) {}

	return 0;
}
