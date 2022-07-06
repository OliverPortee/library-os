#include "machine/vgascr.h"

void VGA_Screen::show(int x, int y, char c) {
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