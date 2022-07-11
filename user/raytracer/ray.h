#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public: 
    Vec3 origin;
    Vec3 direction;
    
    Vec3 origin() const { return origin; }
    Vec3 direction() const { return direction; }

    Vec3 at(double t) const { 
        return origin + t * direction;
    }
};

#endif