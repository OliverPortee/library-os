#ifndef __vga_screen_include__
#define __vga_screen_include__

class VGA_Screen
{
private:
    char *const VGA_BASE_ADDR = (char *)0xA0000;
    
	VGA_Screen(const VGA_Screen &copy); // prevent copying

public:
    const int PIXEL_WIDTH = 320;
    const int PIXEL_HEIGHT = 200;
    const int COLOUR_DEPTH = 8;

	VGA_Screen(){};

	/**
	 * Write char c into the text buffer at position (x, y)
	 * with attribute attrib.
	 */
	void show(int x, int y, char c);

    /**
     * fills the entire screen with the specified color c. 
     */
    void fill(char c);
};

#endif
