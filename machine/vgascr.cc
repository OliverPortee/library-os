#include "machine/vgascr.h"
#include "user/raytracer/vec3.h"

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

    for (int i = 0; i < 256*3; i += 3)
    {
        byte_colour vgacol {
            .r = colour_palette[i],
            .g = colour_palette[i+1],
            .b = colour_palette[i+2]
        };
        
        unsigned dist = manhattan_dist(colour, vgacol);

        if (dist == 0) { return (unsigned char) i / 3; }
        else if (dist < min_dist) 
        {
            min_dist = dist;
            min_index = (unsigned char) (i / 3);
        }
    }

    return min_index;
}

VGA_Screen vga_scr{};