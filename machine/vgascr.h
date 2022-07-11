#ifndef __vga_screen_include__
#define __vga_screen_include__

#include "machine/io_port.h"

class VGA_Screen
{
private:
    char *const VGA_BASE_ADDR = (char *)0xA0000;

    // offset of the current pixel from the VGA_BASE_ADDR
    unsigned int current_pixel_offset = 0;

    // ports used to read color values from the palette RAM
    // see http://www.osdever.net/FreeVGA/vga/colorreg.htm
    const IO_Port dac_read_mode_reg{0x3C7};
    const IO_Port dac_data_reg{0x3C9};

    unsigned char colour_palette[256*3];

	VGA_Screen(const VGA_Screen &copy); // prevent copying

public:
    const int PIXEL_WIDTH = 320;
    const int PIXEL_HEIGHT = 200;
    const int COLOUR_DEPTH = 8;
    const int PIXEL_COUNT = PIXEL_WIDTH * PIXEL_HEIGHT;
    const float ASPECT_RATIO = (float)PIXEL_WIDTH / (float)PIXEL_HEIGHT;

	VGA_Screen();

	/**
	 * Write char c into the text buffer at position (x, y)
	 * with attribute attrib.
	 */
	void show(int x, int y, unsigned char c);

	void show_next(unsigned char c);

    /**
     * fills the entire screen with the specified color c. 
     */
    void fill(unsigned char c);

    void read_colour_palette();

    void rgb_to_yuv(unsigned char r, unsigned char g, unsigned char b);

    void yuv_to_rgb(unsigned char y, unsigned char u, unsigned char v);

    /**
     * converts colours from rgb colour space to the 13h colour palette
     */
    unsigned char match_colour(unsigned char r, unsigned char g, unsigned char b);
};

extern VGA_Screen vga_scr;

#endif
