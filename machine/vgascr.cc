#include "machine/vgascr.h"

VGA_Screen::VGA_Screen() { read_colour_palette(); }

void VGA_Screen::show(int x, int y, unsigned char c) {
    if (x > PIXEL_WIDTH || y < PIXEL_HEIGHT || x < 0 || y < 0) return;
    
    char* pos = VGA_BASE_ADDR + (x + y * PIXEL_WIDTH);
    *pos = c;
}

void VGA_Screen::fill(unsigned char c) {
    char* pos = VGA_BASE_ADDR;
    int bytes_per_pixel = COLOUR_DEPTH / 8;
    int num_pixels = PIXEL_WIDTH*PIXEL_HEIGHT;
    for (int i = 0; i < num_pixels*bytes_per_pixel; i++)
    {
        *pos = c;
        pos += 1; 
    }
}

void VGA_Screen::read_colour_palette() {
    // write index of first colour, it is supposed to 
    // automatically advance after 3 read operations 
    dac_read_mode_reg.outb(0x00);

    // for 256 colours with 3 components each (red, green, blue) 
    for (int i = 0; i < 256*3; i += 3)
    {
        colour_palette[i] = dac_data_reg.inb();      // red
        colour_palette[i+1] = dac_data_reg.inb();    // green
        colour_palette[i+2] = dac_data_reg.inb();    // blue
    }
}

// UNUSED
// transformations between YUV and RGB colour spaces according to:
// https://en.wikipedia.org/wiki/YUV#Y%E2%80%B2UV444_to_RGB888_conversion
void VGA_Screen::rgb_to_yuv(unsigned char r, unsigned char g, unsigned char b) {
    int y = ((66*r + 129*g + 25*b + 128) >> 8) + 16;
    int u = ((-38*r - 74*g - 112*b + 128) >> 8) + 128;
    int v = ((112*r - 94*g - 18*b + 128) >> 8) + 128;
}

// UNUSED
void VGA_Screen::yuv_to_rgb(unsigned char y, unsigned char u, unsigned char v) {
    unsigned char c = y - 16;
    unsigned char d = u - 128;
    unsigned char e = v - 128;

    // TODO: clamp these to 0-255
    unsigned char r = (298*c + 409*e + 128) >> 8;
    unsigned char g = (298*c - 100*d - 208*e + 128) >> 8;
    unsigned char b = (298*c + 516*d + 128) >> 8;
}

int abs(int x) {
    if (x >= 0) return x;
    else return -x;    
}

/**
 * matches an rgb colour to a colour in the mode 13h palette
 */
unsigned char VGA_Screen::match_colour(unsigned char r, unsigned char g, unsigned char b) {
    unsigned int min_dist = 0xffffffff; // == UINT_MAX
    unsigned char min_index = 0;

    for (int i = 0; i < 256*3; i += 3)
    {
        // manhattan distance (use euclidean distance, when possible)
        unsigned int dist = 0;
        dist += abs((r-colour_palette[i]));
        dist += abs((g-colour_palette[i+1]));
        dist += abs((b-colour_palette[i+2]));

        if (dist == 0) { return (unsigned char) i / 3; }
        else if (dist < min_dist) 
        {
            min_dist = dist;
            min_index = (unsigned char) (i / 3);
        }
    }

    return min_index;
}