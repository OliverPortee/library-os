#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public: 
        Point3 origin;
        Point3 direction;
    
    Point3 origin() const { return origin; }
    Vec3 direction() const { return direction; }

    Point3 at(double t) const { 
        return origin + t * direction;
    }
};

#endif