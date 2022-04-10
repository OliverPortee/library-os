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

	/**
	 * Read the character and the attribute
	 * at position (x, y) in the text buffer.
	 */
	void read(int x, int y, char &c, unsigned char &attrib);

	/**
	 * Clear line y starting at position x.
	 */
	void clear_line(unsigned int x, unsigned int y);

	/**
	 * Shift the whole screen up by one line and clear the last line.
	 */
	void shiftup();

public:
	CGA_Screen()
		: index_reg{0x3d4}, data_reg{0x3d5}
	{
	}

	/**
	 * Write char c into the text buffer at position (x, y)
	 * with attribute attrib.
	 */
	void show(int x, int y, char c, unsigned char attrib);

	/**
	 * Set the position of the cursor to (x, y).
	 */
	void setpos(int x, int y);

	/**
	 * Get the position of the cursor.
	 */
	void getpos(int &x, int &y);

	/**
	 * Print the first length chars of text
	 * using the attribute attrib.
	 */
	void print(char *text, int length, unsigned char attrib);
};

#endif
