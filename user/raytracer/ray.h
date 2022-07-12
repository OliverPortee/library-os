#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray {
    Point3 origin;
    Vec3 direction;

    Ray(Point3 origin, Vec3 direction) : origin{origin}, direction{direction} {}
    Ray() = default;

    Point3 at(double t) const { return origin + t * direction; }
};

#endif