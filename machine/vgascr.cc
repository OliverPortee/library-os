#include "machine/vgascr.h"

VGA_Screen::VGA_Screen() { read_colour_palette(); }

void VGA_Screen::show(int x, int y, char c) {
    if (x > PIXEL_WIDTH || y < PIXEL_HEIGHT || x < 0 || y < 0) return;
    
    char* pos = VGA_BASE_ADDR + (x + y * PIXEL_WIDTH);
    *pos = c;
}

void VGA_Screen::fill(char c) {
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
    // write index of first colour, the index is supposed to 
    // automatically advance after 3 read operations 
    dac_read_mode_reg.outb(0x00);
    char* p = &colour_palette[0];

    for (int i = 0; i < 256*3; i += 3)
    {
        *p = dac_data_reg.inb();        // red
        *(p+1) = dac_data_reg.inb();    // green
        *(p+2) = dac_data_reg.inb();    // blue
    }
}

// transformations betweeb YUV and RGB colour spaces according to:
// https://en.wikipedia.org/wiki/YUV#Y%E2%80%B2UV444_to_RGB888_conversion
void VGA_Screen::rgb_to_yuv(char r, char g, char b) {
    int y = ((66*r + 129*g + 25*b + 128) >> 8) + 16;
    int u = ((-38*r - 74*g - 112*b + 128) >> 8) + 128;
    int v = ((112*r - 94*g - 18*b + 128) >> 8) + 128;
}

void VGA_Screen::yuv_to_rgb(char y, char u, char v) {
    char c = y - 16;
    char d = u - 128;
    char e = v - 128;

    // TODO: clamp these to 0-255
    char r = (298*c + 409*e + 128) >> 8;
    char g = (298*c - 100*d - 208*e + 128) >> 8;
    char b = (298*c + 516*d + 128) >> 8;
}

void VGA_Screen::rgb_to_13h(char r, char g, char b) {

}