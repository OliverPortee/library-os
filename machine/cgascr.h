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

class CGA_Screen {
private:
/* Add your code here */
	const int SIZE_X = 80;
	const int SIZE_Y = 25;

	int cursorPosX = 0;
	int cursorPosY = 0;

	CGA_Screen(const CGA_Screen &copy); // prevent copying
public:
	CGA_Screen()
/* Add your code here */ 
{}

/* Add your code here */
	void show(int x, int y, char c, unsigned char attrib);
	void setpos(int x, int y);
	void getpos(int& x, int& y);
	void print(char* text, int length, unsigned char attrib);
};

/* Add your code here */ 

#endif
