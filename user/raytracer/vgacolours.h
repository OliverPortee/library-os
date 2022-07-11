#ifndef __VGA_COLOURS__
#define __VGA_COLOURS__

#include "user/raytracer/utility.h"

struct byte_colour vga_colour_palette[] = {
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0xAA},
    byte_colour{.r=0x00, .g=0xAA, .b=0x00},
    byte_colour{.r=0x00, .g=0xAA, .b=0xAA},
    byte_colour{.r=0xAA, .g=0x00, .b=0x00},
    byte_colour{.r=0xAA, .g=0x00, .b=0xAA},
    byte_colour{.r=0xAA, .g=0x55, .b=0x00},
    byte_colour{.r=0xAA, .g=0xAA, .b=0xAA},
    byte_colour{.r=0x55, .g=0x55, .b=0x55},
    byte_colour{.r=0x55, .g=0x55, .b=0xFF},
    byte_colour{.r=0x55, .g=0xFF, .b=0x55},
    byte_colour{.r=0x55, .g=0xFF, .b=0xFF},
    byte_colour{.r=0xFF, .g=0x55, .b=0x55},
    byte_colour{.r=0xFF, .g=0x55, .b=0xFF},
    byte_colour{.r=0xFF, .g=0xFF, .b=0x55},
    byte_colour{.r=0xFF, .g=0xFF, .b=0xFF},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x10, .g=0x10, .b=0x10},
    byte_colour{.r=0x20, .g=0x20, .b=0x20},
    byte_colour{.r=0x35, .g=0x35, .b=0x35},
    byte_colour{.r=0x45, .g=0x45, .b=0x45},
    byte_colour{.r=0x55, .g=0x55, .b=0x55},
    byte_colour{.r=0x65, .g=0x65, .b=0x65},
    byte_colour{.r=0x75, .g=0x75, .b=0x75},
    byte_colour{.r=0x8A, .g=0x8A, .b=0x8A},
    byte_colour{.r=0x9A, .g=0x9A, .b=0x9A},
    byte_colour{.r=0xAA, .g=0xAA, .b=0xAA},
    byte_colour{.r=0xBA, .g=0xBA, .b=0xBA},
    byte_colour{.r=0xCA, .g=0xCA, .b=0xCA},
    byte_colour{.r=0xDF, .g=0xDF, .b=0xDF},
    byte_colour{.r=0xEF, .g=0xEF, .b=0xEF},
    byte_colour{.r=0xFF, .g=0xFF, .b=0xFF},
    byte_colour{.r=0x00, .g=0x00, .b=0xFF},
    byte_colour{.r=0x41, .g=0x00, .b=0xFF},
    byte_colour{.r=0x82, .g=0x00, .b=0xFF},
    byte_colour{.r=0xBE, .g=0x00, .b=0xFF},
    byte_colour{.r=0xFF, .g=0x00, .b=0xFF},
    byte_colour{.r=0xFF, .g=0x00, .b=0xBE},
    byte_colour{.r=0xFF, .g=0x00, .b=0x82},
    byte_colour{.r=0xFF, .g=0x00, .b=0x41},
    byte_colour{.r=0xFF, .g=0x00, .b=0x00},
    byte_colour{.r=0xFF, .g=0x41, .b=0x00},
    byte_colour{.r=0xFF, .g=0x82, .b=0x00},
    byte_colour{.r=0xFF, .g=0xBE, .b=0x00},
    byte_colour{.r=0xFF, .g=0xFF, .b=0x00},
    byte_colour{.r=0xBE, .g=0xFF, .b=0x00},
    byte_colour{.r=0x82, .g=0xFF, .b=0x00},
    byte_colour{.r=0x41, .g=0xFF, .b=0x00},
    byte_colour{.r=0x00, .g=0xFF, .b=0x00},
    byte_colour{.r=0x00, .g=0xFF, .b=0x41},
    byte_colour{.r=0x00, .g=0xFF, .b=0x82},
    byte_colour{.r=0x00, .g=0xFF, .b=0xBE},
    byte_colour{.r=0x00, .g=0xFF, .b=0xFF},
    byte_colour{.r=0x00, .g=0xBE, .b=0xFF},
    byte_colour{.r=0x00, .g=0x82, .b=0xFF},
    byte_colour{.r=0x00, .g=0x41, .b=0xFF},
    byte_colour{.r=0x82, .g=0x82, .b=0xFF},
    byte_colour{.r=0x9E, .g=0x82, .b=0xFF},
    byte_colour{.r=0xBE, .g=0x82, .b=0xFF},
    byte_colour{.r=0xDF, .g=0x82, .b=0xFF},
    byte_colour{.r=0xFF, .g=0x82, .b=0xFF},
    byte_colour{.r=0xFF, .g=0x82, .b=0xDF},
    byte_colour{.r=0xFF, .g=0x82, .b=0xBE},
    byte_colour{.r=0xFF, .g=0x82, .b=0x9E},
    byte_colour{.r=0xFF, .g=0x82, .b=0x82},
    byte_colour{.r=0xFF, .g=0x9E, .b=0x82},
    byte_colour{.r=0xFF, .g=0xBE, .b=0x82},
    byte_colour{.r=0xFF, .g=0xDF, .b=0x82},
    byte_colour{.r=0xFF, .g=0xFF, .b=0x82},
    byte_colour{.r=0xDF, .g=0xFF, .b=0x82},
    byte_colour{.r=0xBE, .g=0xFF, .b=0x82},
    byte_colour{.r=0x9E, .g=0xFF, .b=0x82},
    byte_colour{.r=0x82, .g=0xFF, .b=0x82},
    byte_colour{.r=0x82, .g=0xFF, .b=0x9E},
    byte_colour{.r=0x82, .g=0xFF, .b=0xBE},
    byte_colour{.r=0x82, .g=0xFF, .b=0xDF},
    byte_colour{.r=0x82, .g=0xFF, .b=0xFF},
    byte_colour{.r=0x82, .g=0xDF, .b=0xFF},
    byte_colour{.r=0x82, .g=0xBE, .b=0xFF},
    byte_colour{.r=0x82, .g=0x9E, .b=0xFF},
    byte_colour{.r=0xBA, .g=0xBA, .b=0xFF},
    byte_colour{.r=0xCA, .g=0xBA, .b=0xFF},
    byte_colour{.r=0xDF, .g=0xBA, .b=0xFF},
    byte_colour{.r=0xEF, .g=0xBA, .b=0xFF},
    byte_colour{.r=0xFF, .g=0xBA, .b=0xFF},
    byte_colour{.r=0xFF, .g=0xBA, .b=0xEF},
    byte_colour{.r=0xFF, .g=0xBA, .b=0xDF},
    byte_colour{.r=0xFF, .g=0xBA, .b=0xCA},
    byte_colour{.r=0xFF, .g=0xBA, .b=0xBA},
    byte_colour{.r=0xFF, .g=0xCA, .b=0xBA},
    byte_colour{.r=0xFF, .g=0xDF, .b=0xBA},
    byte_colour{.r=0xFF, .g=0xEF, .b=0xBA},
    byte_colour{.r=0xFF, .g=0xFF, .b=0xBA},
    byte_colour{.r=0xEF, .g=0xFF, .b=0xBA},
    byte_colour{.r=0xDF, .g=0xFF, .b=0xBA},
    byte_colour{.r=0xCA, .g=0xFF, .b=0xBA},
    byte_colour{.r=0xBA, .g=0xFF, .b=0xBA},
    byte_colour{.r=0xBA, .g=0xFF, .b=0xCA},
    byte_colour{.r=0xBA, .g=0xFF, .b=0xDF},
    byte_colour{.r=0xBA, .g=0xFF, .b=0xEF},
    byte_colour{.r=0xBA, .g=0xFF, .b=0xFF},
    byte_colour{.r=0xBA, .g=0xEF, .b=0xFF},
    byte_colour{.r=0xBA, .g=0xDF, .b=0xFF},
    byte_colour{.r=0xBA, .g=0xCA, .b=0xFF},
    byte_colour{.r=0x00, .g=0x00, .b=0x71},
    byte_colour{.r=0x1C, .g=0x00, .b=0x71},
    byte_colour{.r=0x39, .g=0x00, .b=0x71},
    byte_colour{.r=0x55, .g=0x00, .b=0x71},
    byte_colour{.r=0x71, .g=0x00, .b=0x71},
    byte_colour{.r=0x71, .g=0x00, .b=0x55},
    byte_colour{.r=0x71, .g=0x00, .b=0x39},
    byte_colour{.r=0x71, .g=0x00, .b=0x1C},
    byte_colour{.r=0x71, .g=0x00, .b=0x00},
    byte_colour{.r=0x71, .g=0x1C, .b=0x00},
    byte_colour{.r=0x71, .g=0x39, .b=0x00},
    byte_colour{.r=0x71, .g=0x55, .b=0x00},
    byte_colour{.r=0x71, .g=0x71, .b=0x00},
    byte_colour{.r=0x55, .g=0x71, .b=0x00},
    byte_colour{.r=0x39, .g=0x71, .b=0x00},
    byte_colour{.r=0x1C, .g=0x71, .b=0x00},
    byte_colour{.r=0x00, .g=0x71, .b=0x00},
    byte_colour{.r=0x00, .g=0x71, .b=0x1C},
    byte_colour{.r=0x00, .g=0x71, .b=0x39},
    byte_colour{.r=0x00, .g=0x71, .b=0x55},
    byte_colour{.r=0x00, .g=0x71, .b=0x71},
    byte_colour{.r=0x00, .g=0x55, .b=0x71},
    byte_colour{.r=0x00, .g=0x39, .b=0x71},
    byte_colour{.r=0x00, .g=0x1C, .b=0x71},
    byte_colour{.r=0x39, .g=0x39, .b=0x71},
    byte_colour{.r=0x45, .g=0x39, .b=0x71},
    byte_colour{.r=0x55, .g=0x39, .b=0x71},
    byte_colour{.r=0x61, .g=0x39, .b=0x71},
    byte_colour{.r=0x71, .g=0x39, .b=0x71},
    byte_colour{.r=0x71, .g=0x39, .b=0x61},
    byte_colour{.r=0x71, .g=0x39, .b=0x55},
    byte_colour{.r=0x71, .g=0x39, .b=0x45},
    byte_colour{.r=0x71, .g=0x39, .b=0x39},
    byte_colour{.r=0x71, .g=0x45, .b=0x39},
    byte_colour{.r=0x71, .g=0x55, .b=0x39},
    byte_colour{.r=0x71, .g=0x61, .b=0x39},
    byte_colour{.r=0x71, .g=0x71, .b=0x39},
    byte_colour{.r=0x61, .g=0x71, .b=0x39},
    byte_colour{.r=0x55, .g=0x71, .b=0x39},
    byte_colour{.r=0x45, .g=0x71, .b=0x39},
    byte_colour{.r=0x39, .g=0x71, .b=0x39},
    byte_colour{.r=0x39, .g=0x71, .b=0x45},
    byte_colour{.r=0x39, .g=0x71, .b=0x55},
    byte_colour{.r=0x39, .g=0x71, .b=0x61},
    byte_colour{.r=0x39, .g=0x71, .b=0x71},
    byte_colour{.r=0x39, .g=0x61, .b=0x71},
    byte_colour{.r=0x39, .g=0x55, .b=0x71},
    byte_colour{.r=0x39, .g=0x45, .b=0x71},
    byte_colour{.r=0x51, .g=0x51, .b=0x71},
    byte_colour{.r=0x59, .g=0x51, .b=0x71},
    byte_colour{.r=0x61, .g=0x51, .b=0x71},
    byte_colour{.r=0x69, .g=0x51, .b=0x71},
    byte_colour{.r=0x71, .g=0x51, .b=0x71},
    byte_colour{.r=0x71, .g=0x51, .b=0x69},
    byte_colour{.r=0x71, .g=0x51, .b=0x61},
    byte_colour{.r=0x71, .g=0x51, .b=0x59},
    byte_colour{.r=0x71, .g=0x51, .b=0x51},
    byte_colour{.r=0x71, .g=0x59, .b=0x51},
    byte_colour{.r=0x71, .g=0x61, .b=0x51},
    byte_colour{.r=0x71, .g=0x69, .b=0x51},
    byte_colour{.r=0x71, .g=0x71, .b=0x51},
    byte_colour{.r=0x69, .g=0x71, .b=0x51},
    byte_colour{.r=0x61, .g=0x71, .b=0x51},
    byte_colour{.r=0x59, .g=0x71, .b=0x51},
    byte_colour{.r=0x51, .g=0x71, .b=0x51},
    byte_colour{.r=0x51, .g=0x71, .b=0x59},
    byte_colour{.r=0x51, .g=0x71, .b=0x61},
    byte_colour{.r=0x51, .g=0x71, .b=0x69},
    byte_colour{.r=0x51, .g=0x71, .b=0x71},
    byte_colour{.r=0x51, .g=0x69, .b=0x71},
    byte_colour{.r=0x51, .g=0x61, .b=0x71},
    byte_colour{.r=0x51, .g=0x59, .b=0x71},
    byte_colour{.r=0x00, .g=0x00, .b=0x41},
    byte_colour{.r=0x10, .g=0x00, .b=0x41},
    byte_colour{.r=0x20, .g=0x00, .b=0x41},
    byte_colour{.r=0x31, .g=0x00, .b=0x41},
    byte_colour{.r=0x41, .g=0x00, .b=0x41},
    byte_colour{.r=0x41, .g=0x00, .b=0x31},
    byte_colour{.r=0x41, .g=0x00, .b=0x20},
    byte_colour{.r=0x41, .g=0x00, .b=0x10},
    byte_colour{.r=0x41, .g=0x00, .b=0x00},
    byte_colour{.r=0x41, .g=0x10, .b=0x00},
    byte_colour{.r=0x41, .g=0x20, .b=0x00},
    byte_colour{.r=0x41, .g=0x31, .b=0x00},
    byte_colour{.r=0x41, .g=0x41, .b=0x00},
    byte_colour{.r=0x31, .g=0x41, .b=0x00},
    byte_colour{.r=0x20, .g=0x41, .b=0x00},
    byte_colour{.r=0x10, .g=0x41, .b=0x00},
    byte_colour{.r=0x00, .g=0x41, .b=0x00},
    byte_colour{.r=0x00, .g=0x41, .b=0x10},
    byte_colour{.r=0x00, .g=0x41, .b=0x20},
    byte_colour{.r=0x00, .g=0x41, .b=0x31},
    byte_colour{.r=0x00, .g=0x41, .b=0x41},
    byte_colour{.r=0x00, .g=0x31, .b=0x41},
    byte_colour{.r=0x00, .g=0x20, .b=0x41},
    byte_colour{.r=0x00, .g=0x10, .b=0x41},
    byte_colour{.r=0x20, .g=0x20, .b=0x41},
    byte_colour{.r=0x28, .g=0x20, .b=0x41},
    byte_colour{.r=0x31, .g=0x20, .b=0x41},
    byte_colour{.r=0x39, .g=0x20, .b=0x41},
    byte_colour{.r=0x41, .g=0x20, .b=0x41},
    byte_colour{.r=0x41, .g=0x20, .b=0x39},
    byte_colour{.r=0x41, .g=0x20, .b=0x31},
    byte_colour{.r=0x41, .g=0x20, .b=0x28},
    byte_colour{.r=0x41, .g=0x20, .b=0x20},
    byte_colour{.r=0x41, .g=0x28, .b=0x20},
    byte_colour{.r=0x41, .g=0x31, .b=0x20},
    byte_colour{.r=0x41, .g=0x39, .b=0x20},
    byte_colour{.r=0x41, .g=0x41, .b=0x20},
    byte_colour{.r=0x39, .g=0x41, .b=0x20},
    byte_colour{.r=0x31, .g=0x41, .b=0x20},
    byte_colour{.r=0x28, .g=0x41, .b=0x20},
    byte_colour{.r=0x20, .g=0x41, .b=0x20},
    byte_colour{.r=0x20, .g=0x41, .b=0x28},
    byte_colour{.r=0x20, .g=0x41, .b=0x31},
    byte_colour{.r=0x20, .g=0x41, .b=0x39},
    byte_colour{.r=0x20, .g=0x41, .b=0x41},
    byte_colour{.r=0x20, .g=0x39, .b=0x41},
    byte_colour{.r=0x20, .g=0x31, .b=0x41},
    byte_colour{.r=0x20, .g=0x28, .b=0x41},
    byte_colour{.r=0x2D, .g=0x2D, .b=0x41},
    byte_colour{.r=0x31, .g=0x2D, .b=0x41},
    byte_colour{.r=0x35, .g=0x2D, .b=0x41},
    byte_colour{.r=0x3D, .g=0x2D, .b=0x41},
    byte_colour{.r=0x41, .g=0x2D, .b=0x41},
    byte_colour{.r=0x41, .g=0x2D, .b=0x3D},
    byte_colour{.r=0x41, .g=0x2D, .b=0x35},
    byte_colour{.r=0x41, .g=0x2D, .b=0x31},
    byte_colour{.r=0x41, .g=0x2D, .b=0x2D},
    byte_colour{.r=0x41, .g=0x31, .b=0x2D},
    byte_colour{.r=0x41, .g=0x35, .b=0x2D},
    byte_colour{.r=0x41, .g=0x3D, .b=0x2D},
    byte_colour{.r=0x41, .g=0x41, .b=0x2D},
    byte_colour{.r=0x3D, .g=0x41, .b=0x2D},
    byte_colour{.r=0x35, .g=0x41, .b=0x2D},
    byte_colour{.r=0x31, .g=0x41, .b=0x2D},
    byte_colour{.r=0x2D, .g=0x41, .b=0x2D},
    byte_colour{.r=0x2D, .g=0x41, .b=0x31},
    byte_colour{.r=0x2D, .g=0x41, .b=0x35},
    byte_colour{.r=0x2D, .g=0x41, .b=0x3D},
    byte_colour{.r=0x2D, .g=0x41, .b=0x41},
    byte_colour{.r=0x2D, .g=0x3D, .b=0x41},
    byte_colour{.r=0x2D, .g=0x35, .b=0x41},
    byte_colour{.r=0x2D, .g=0x31, .b=0x41},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00},
    byte_colour{.r=0x00, .g=0x00, .b=0x00}
};

#endif