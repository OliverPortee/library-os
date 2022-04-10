#ifndef __screen_include__
#define __screen_include__

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* This class allows accessing the PC's screen.  Accesses work directly on   */
/* the hardware level, i.e. via the video memory and the graphic adapter's   */
/* I/O ports.                                                                */
/*****************************************************************************/

#include "machine/io_port.h"

class CGA_Screen
{
private:
	IO_Port index_reg;
	IO_Port data_reg;

	CGA_Screen(const CGA_Screen &copy); // prevent copying
public:
	CGA_Screen()
		: index_reg{0x3d4}, data_reg{0x3d5}
	{
	}

	void show(int x, int y, char c, unsigned char attrib);

	void setpos(int x, int y);
	void getpos(int &x, int &y);
};

/* Add your code here */

#endif
