
#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "ray.h"
#include "vec3.h"

struct HitInfo {
    Point3 point;
    Vec3 normal;
    double t;
};

struct Hittable {
    virtual bool hit(const Ray& ray, double t_min, double t_max,
                     HitInfo& out_hitinfo) = 0;
};

#endif
