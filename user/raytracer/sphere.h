

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "hittable.h"
#include "material.h"
#include "vec3.h"

struct Sphere : public Hittable {
    Sphere() = default;
    Sphere(Point3 center, double radius, Material* material)
        : center{center}, radius{radius}, material{material} {}

    virtual bool hit(const Ray& ray, double t_min, double t_max,
                     HitInfo& out_hitinfo);

    Point3 center;
    double radius;
    Material* material;
};

#endif