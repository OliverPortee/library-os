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

/* Add your code here */ 
void CGA_Screen::show(int x, int y, char c, unsigned char attrib) {
    char* CGA_START = (char *)0xb800;
    char* pos = CGA_START + 2*(x + y*SIZE_Y);
    *pos = c;
    *(pos + 1) = attrib;
}

void CGA_Screen::setpos(int x, int y) {
    if (x < SIZE_X && y < SIZE_Y) {
        cursorPosX = x;
        cursorPosY = y;
    }
}

void CGA_Screen::getpos(int& x, int& y) {
    x = cursorPosX;
    y = cursorPosY; 
}

void CGA_Screen::print(char* text, int length, unsigned char attrib) {
    char c; 

    for (int i = 0; i < length; i++)
    {
        c = *(text + i);

        if (c == '\n') {
            cursorPosX = 0;
            cursorPosY += 1;    // TODO: missing scrolling
            continue;
        }

        show(cursorPosX, cursorPosY, *(text + i), attrib);

        if (cursorPosX < SIZE_X - 1) {
            cursorPosX += 1;
        } else {
            cursorPosX = 0;
            cursorPosY += 1;    // TODO: missing scrolling
        }
    }
}
