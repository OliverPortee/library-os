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
const int CURSOR_HIGH = 14;
const int CURSOR_LOW = 15;

void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    {
        return;
    }
    char *const pos = CGA_START + (x + WIDTH * y) * 2;
    *pos = c;
    *(pos + 1) = attrib;
}

void CGA_Screen::setpos(int x, int y)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    {
        return;
    }
    const unsigned int pos = y * WIDTH + x;
    
    index_reg.outb(CURSOR_HIGH);
    data_reg.outb((pos & 0xff00) >> 8);
    index_reg.outb(CURSOR_LOW);
    data_reg.outb(pos & 0x00ff);
}

void CGA_Screen::getpos(int &x, int &y)
{
    index_reg.outb(CURSOR_HIGH);
    const unsigned int high = data_reg.inb();
    index_reg.outb(CURSOR_LOW);
    const unsigned int low = data_reg.inb();

    const unsigned int pos = (high << 8) | low;
    x = pos % WIDTH;
    y = pos / WIDTH;
}

void CGA_Screen::clear_line(unsigned int x, unsigned int y)
{
    for (unsigned int pos = x; pos < WIDTH; ++pos)
    {
        show(pos, y, ' ', 0x0f);
    }
}

void CGA_Screen::read(int x, int y, char &c, unsigned char &attrib)
{
    char *const pos = CGA_START + (x + WIDTH * y) * 2;
    c = *pos;
    attrib = *(pos + 1);
}

void CGA_Screen::shiftup()
{
    char c;
    unsigned char attr;
    for (unsigned int y = 1; y < HEIGHT; ++y)
    {
        for (unsigned int x = 0; x < WIDTH; ++x)
        {
            read(x, y, c, attr);
            show(x, y - 1, c, attr);
        }
    }
    clear_line(0, HEIGHT - 1);
}

void CGA_Screen::print(char *text, int length, unsigned char attrib)
{
    if (length <= 0)
    {
        return;
    }

    int curx, cury;
    
    getpos(curx, cury);

    for (int i = 0; i < length; ++i)
    {
        if (text[i] == '\n')
        {
            // if a line has exactly 80 characters (followed by a newline),
            // we don't want to write two newlines
            if (i == 0 || (curx != 0 && text[i - 1] != '\n'))
            {
                clear_line(curx, cury);
                ++cury;
                curx = 0;
            }
        }
        else
        {
            show(curx++, cury, text[i], attrib);
            if (curx >= WIDTH)
            {
                ++cury;
                curx = 0;
            }
        }
        if (cury >= HEIGHT)
        {
            shiftup();
            --cury;
        }
    }
    setpos(curx, cury);
}
