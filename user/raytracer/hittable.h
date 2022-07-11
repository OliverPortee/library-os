
#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include "ray.h"
#include "vec3.h"

struct HitInfo {
    Point3 point;
    Vec3 normal;
    double t;
    bool hit_front_face;

    void set_normal(const Ray& ray, const Vec3& outward_normal) {
        hit_front_face = dot(ray.direction, outward_normal) < 0;
        normal = hit_front_face ? outward_normal : -outward_normal;
    }
};

struct Hittable {
    virtual bool hit(const Ray& ray, double t_min, double t_max,
                     HitInfo& out_hitinfo) = 0;
};

#endif
