#ifndef __UTILITY_H__
#define __UTILITY_H__

// RGB colour with 1 byte per component
struct byte_colour { unsigned char r,g,b; };

// math constants and functions

const double INFINITY = 1.79769e+308;
const double PI = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

#endif