
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "ray.h"
#include "vec3.h"
#include "hittable.h"

struct HitInfo;

struct Material {
    virtual bool scatter(const Ray& ray, const HitInfo& hinfo,
                         Color& attenuation, Ray& scattered) const = 0;
};

struct Lambertian : Material {
    Lambertian(const Color& albedo) : albedo{albedo} {}

    virtual bool scatter(const Ray& ray, const HitInfo& hinfo,
                         Color& attenuation, Ray& scattered) const {
        auto scatter_direction = hinfo.normal + Vec3::random_unit_vec();

        // avoiding near zero scatter directions
        if (scatter_direction.near_zero()) scatter_direction = hinfo.normal;

        scattered = Ray(hinfo.point, scatter_direction);
        attenuation = albedo;
        return true;
    }

    Color albedo;
};

class Metal : public Material {
   public:
    Metal(const Color& albedo) : albedo(albedo) {}

    virtual bool scatter(const Ray& ray, const HitInfo& hinfo,
                         Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = ray.direction.normalized().reflect(hinfo.normal);
        scattered = Ray(hinfo.point, reflected);
        attenuation = albedo;
        return dot(scattered.direction, hinfo.normal) > 0;
    }

   public:
    Color albedo;
};

#endif