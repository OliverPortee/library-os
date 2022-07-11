
#include "hittable.h"
#include "vec3.h"

struct Sphere : public Hittable {
    Sphere() = default;
    Sphere(Point3 center, double radius) : center{center}, radius{radius} {}

    virtual bool hit(const Ray& ray, double t_min, double t_max,
                     HitInfo& out_hitinfo);

    Point3 center;
    double radius;
};