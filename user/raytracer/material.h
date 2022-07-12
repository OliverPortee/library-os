
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include "object/assert.h"

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
    Metal(const Color& albedo, double fuzziness) : albedo(albedo), fuzziness{fuzziness} {
        assert(fuzziness >= 0 && fuzziness <= 1, "Metal: fuzziness in wrong range");
    }

    virtual bool scatter(const Ray& ray, const HitInfo& hinfo,
                         Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = ray.direction.normalized().reflect(hinfo.normal);
        scattered = Ray(hinfo.point, reflected + fuzziness * Vec3::random_length_smaller_1());
        attenuation = albedo;
        return dot(scattered.direction, hinfo.normal) > 0;
    }

   public:
    Color albedo;
    double fuzziness;
};

class Dielectric : public Material {
   public:
    Dielectric(double index_of_refraction) : ior(index_of_refraction) {}

    virtual bool scatter(const Ray& ray_in, const HitInfo& hit_info,
                         Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1.0, 1.0, 1.0);
        double refraction_ratio = hit_info.hit_front_face ? (1.0 / ior) : ior;

        Vec3 normalized_dir = ray_in.direction.normalized();
        
        double dotp = dot(-normalized_dir, hit_info.normal);
        double cos_theta = (dotp < 1.0) ? dotp : 1.0; 
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        bool cannot_refract = refraction_ratio * sin_theta > 1;
        Vec3 direction;

        if (cannot_refract) 
            direction = normalized_dir.reflect(hit_info.normal);
        else 
            direction = normalized_dir.refract(hit_info.normal, refraction_ratio);

        scattered = Ray(hit_info.point, direction);
        return true;
    }

   public:  
    // the index of refraction
    double ior;
};

#endif