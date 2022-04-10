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

#include "machine/cgascr.h"

char *const CGA_START = (char *)0xb8000;
const int WIDTH = 80;
const int HEIGHT = 25;

void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) {
        return;
    }
    char *const pos = CGA_START + (x + WIDTH * y) * 2;
    *pos = c;
    *(pos + 1) = attrib;
}

void CGA_Screen::setpos(int x, int y)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT) {
        return;
    }
    const unsigned int pos = y * WIDTH + x;
    index_reg.outw(14);
    data_reg.outw((pos & 0xff00) >> 8);
    index_reg.outw(15);
    data_reg.outw(pos & 0x00ff);
}

void CGA_Screen::getpos(int &x, int &y)
{
    index_reg.outb(14);
    const unsigned int high = data_reg.inb();
    index_reg.outb(15);
    const unsigned int low = data_reg.inb();
    const unsigned int pos = (high << 8) | low;
    x = pos % WIDTH;
    y = pos / WIDTH;
}
