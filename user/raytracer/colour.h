#ifndef __COLOUR_H__
#define __COLOUR_H__

#include "user/raytracer/vec3.h"
#include "machine/vgascr.h"

// RGB Color with components normalized to [0,1]
using Color = Vec3;

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void write_pixel(Color col, int samples_per_pixel) {
    
    // Division by AA sample count and gamma correction (for gamma=2.0)
    auto scale = 1.0 / samples_per_pixel; 
    auto r = sqrt(scale * col.x);
    auto g = sqrt(scale * col.y);
    auto b = sqrt(scale * col.z);

    struct byte_colour rgb_bytes {
        .r = static_cast<unsigned char>(256 * clamp(r, 0, 0.9999)),
        .g = static_cast<unsigned char>(256 * clamp(g, 0, 0.9999)),
        .b = static_cast<unsigned char>(256 * clamp(b, 0, 0.9999))
    };
    
    unsigned char colour_index = vga_scr.match_colour(rgb_bytes);
    vga_scr.show_next(colour_index);
}

#endif