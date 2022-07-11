#include "machine/vgascr.h"
#include "user/raytracer/vec3.h"
#include "user/raytracer/vgacolours.h"

VGA_Screen::VGA_Screen() { read_colour_palette(); }

void VGA_Screen::show(int x, int y, unsigned char c) {
    if (x > PIXEL_WIDTH || y > PIXEL_HEIGHT || x < 0 || y < 0) return;
    
    char* pos = VGA_BASE_ADDR + (x + y * PIXEL_WIDTH);
    *pos = c;
}

// writes colour c to the current pixel, then increments current 
void VGA_Screen::show_next(unsigned char c) {
    *(VGA_BASE_ADDR + current_pixel_offset) = c;

    if (current_pixel_offset < PIXEL_COUNT) {
        // move to next pixel
        current_pixel_offset += 1;   
    } else {
        // wrap around to first pixel
        current_pixel_offset = 0;
    }
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
    // write index of first colour (==0), it is supposed to auto-increment
    // to the next colour palette entry after 3 read operations 
    dac_read_mode_reg.outb(0);

    // for 256 colours of the vga colour palette 
    for (int i = 0; i < 256; i++)
    {
        struct byte_colour entry {
            .r = (unsigned char) (dac_data_reg.inb()),
            .g = (unsigned char) (dac_data_reg.inb()),
            .b = (unsigned char) (dac_data_reg.inb())
        };

        colour_palette[i] = entry;
    }
}

int abs(int x) {
    if (x >= 0) return x;
    else return -x;    
}

inline unsigned int square(int x) {
    return x*x;
}

// returns the manhattan distance between two colour vectors
unsigned int manhattan_dist(byte_colour& col1, byte_colour& col2) {
    return  abs(col1.r - col2.r) + 
            abs(col1.g - col2.g) + 
            abs(col1.b - col2.b);
}

// returns the euclidean distance between two colour vectors
unsigned int euclidean_dist(byte_colour& col1, byte_colour& col2) {
    unsigned int sum_of_squares = square(col1.r - col2.r);
    sum_of_squares += square(col1.g - col2.g);
    sum_of_squares += square(col1.b - col2.b);
    return sqrt(sum_of_squares);
}

/**
 * matches an rgb colour to a colour in the mode 13h palette
 */
unsigned char VGA_Screen::match_colour(byte_colour colour) {
    unsigned int min_dist = 0xffffffff; // == UINT_MAX
    unsigned char min_index = 0;

    for (int i = 0; i < 256; i++)
    {   

        unsigned dist = manhattan_dist(colour, vga_colour_palette[i]);

        if (dist == 0) { return i; }
        else if (dist < min_dist) 
        {
            min_dist = dist;
            min_index = i;
        }
    }

    return min_index;
}

VGA_Screen vga_scr{};