#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray {
    Point3 origin;
    Point3 direction;

    Point3 at(double t) const { return origin + t * direction; }
};

#endif