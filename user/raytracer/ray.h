#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public: 
        point3 origin;
        point3 direction;
    
    point3 origin() const { return origin; }
    vec3 direction() const { return direction; }

    point3 at(double t) const { 
        return origin + t * direction;
    }
};

#endif