#ifndef __COLOUR_H__
#define __COLOUR_H__

#include "user/raytracer/vec3.h"
#include "machine/vgascr.h"

// RGB values normalized to [0,1]
using colour = Vec3;

void write_pixel(colour col) {
    unsigned char r = static_cast<int>(255.999 * col.x);
    unsigned char g = static_cast<int>(255.999 * col.y);
    unsigned char b = static_cast<int>(255.999 * col.z);

    unsigned char colour_index = vga_scr.match_colour(r,g,b);
    vga_scr.show_next(colour_index);
}

#endif