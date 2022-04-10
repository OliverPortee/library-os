#include "machine/cgascr.h"

int main()
{

	CGA_Screen screen{};
	screen.show(0, 0, '0', 0x0f);
	screen.show(10, 0, '1', 0x0f);
	screen.show(20, 0, '2', 0x0f);
	screen.show(30, 0, '3', 0x0f);
	screen.show(40, 0, '4', 0x0f);
	screen.show(50, 0, '5', 0x0f);
	screen.show(60, 0, '6', 0x0f);
	screen.show(70, 0, '7', 0x0f);
	screen.show(79, 0, 'e', 0x0f);
	screen.show(0, 5, '0', 0x0f);
	screen.show(0, 10, '1', 0x0f);
	screen.show(0, 15, '5', 0x0f);
	screen.show(0, 20, '2', 0x0f);
	screen.show(0, 24, 'e', 0x0f);
	screen.show(79, 24, 'e', 0x0f);
	screen.setpos(7, 3);
	int x, y;
	screen.getpos(x, y);
	screen.show(0, 1, (char)x + '0', 0x0f);
	screen.show(3, 1, (char)y + '0', 0x0f);
	
	return 0;
}
