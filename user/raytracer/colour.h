#ifndef __COLOUR_H__
#define __COLOUR_H__

#include "user/raytracer/vec3.h"
#include "machine/vgascr.h"

// RGB colour with components normalized to [0,1]
using colour = Vec3;

void write_pixel(colour col) {
    struct byte_colour rgb_bytes {
        .r = static_cast<unsigned char>(255.999 * col.x),
        .g = static_cast<unsigned char>(255.999 * col.y),
        .b = static_cast<unsigned char>(255.999 * col.z)
    };

    unsigned char colour_index = vga_scr.match_colour(rgb_bytes);
    vga_scr.show_next(colour_index);
}

#endif