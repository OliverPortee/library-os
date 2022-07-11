
#include "sphere.h"

bool Sphere::hit(const Ray& ray, double t_min, double t_max,
                 HitInfo& out_hitinfo) {
    Vec3 oc = ray.origin - center;
    auto a = ray.direction.length_squared();
    auto half_b = dot(oc, ray.direction);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) return false;
    }

    out_hitinfo.t = root;
    out_hitinfo.point = ray.at(out_hitinfo.t);
    Vec3 outward_normal = (out_hitinfo.point - center) / radius;
    out_hitinfo.set_normal(ray, outward_normal);

    return true;
}