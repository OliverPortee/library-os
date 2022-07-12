
#include "user/raytracer/rt_app.h"
#include "machine/vgascr.h"
#include "user/raytracer/camera.h"
#include "user/raytracer/hittable_list.h"
#include "user/raytracer/ray.h"
#include "user/raytracer/sphere.h"
#include "user/raytracer/utility.h"
#include "user/raytracer/colour.h"
#include "user/raytracer/secret.h"

char stack_rt[65536];

Raytracer::Raytracer() : Thread{stack_rt + sizeof(stack_rt)} {}

void Raytracer::action() {
    if (selected_scene == Scene::demo) render();
    else render_secret();
}

void Raytracer::set_scene(Scene s) { selected_scene = s; }

Color Raytracer::ray_color(const Ray& ray, /*const?*/ Hittable& scene, int depth) {
    HitInfo hinfo;

    if (depth <= 0) return Color(0, 0, 0);

    if (scene.hit(ray, 0.001, INFINITY, hinfo)) {
        Ray scattered;
        Color attenuation;
        if (hinfo.material->scatter(ray, hinfo, attenuation, scattered)) {
            return attenuation * ray_color(scattered, scene, depth - 1);
        }
        return Color();
    }

    Vec3 unit_dir = ray.direction.normalized();
    auto t = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

void Raytracer::render() {
    erase();

    // image properties
    const int img_width = vga_scr.PIXEL_WIDTH;
    const int img_height = vga_scr.PIXEL_HEIGHT;
    const int max_ray_recursion_depth = 50;
    const int samples_per_pixel = 20;

    Lambertian mat_ground{Color(0.8, 0.8, 0)};
    Lambertian mat_center{Color(0.1, 0.2, 0.5)};
    Metal mat_right{Color(0.8, 0.6, 0.2), 0.5};
    Dielectric mat_glass{1.45};

    Sphere left{Point3(-1, 0, -1), 0.4, &mat_glass};
    Sphere center{Point3(0, 0, -1), 0.5, &mat_center};
    Sphere right{Point3(1, 0, -1), 0.5, &mat_right};
    Sphere ground{Point3(0.0, -100.5, -1.0), 100.0, &mat_ground};
    
    HittableList scene;
    scene.add(ground);
    scene.add(left);
    scene.add(center);
    scene.add(right);

    Camera camera;

    // rendering
    for (int j = img_height - 1; j >= 0; --j) {
        for (int i = 0; i < img_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int n = 0; n < samples_per_pixel; ++n) {
                auto u = (i + random.random_double()) / (img_width - 1);
                auto v = (j + random.random_double()) / (img_height - 1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, scene, max_ray_recursion_depth);
            }
            write_pixel(pixel_color, samples_per_pixel);
        }
    }
}

void Raytracer::render_secret() {
    erase();

    const int sphere_count = 263;
    Sphere spheres[sphere_count];

    /*
    Lambertian diffuse_mats[3] = {
        Lambertian {Color(0.4, 0.0, 0.86)},  // purple
        Lambertian {Color(0.86, 0.37, 0.0)}, // orange
        Lambertian {Color(0.01, 0.15, 0.5)}, // dark blue
    };

    Metal metals[3] = {
        Metal {Color(0.72, 0.45, 0.2), 0.1},  // copper
        Metal {Color(0.83, 0.69, 0.22), 0.2}, // gold
        Metal {Color(0.77, 0.83, 0.88), 0.5}, // blue-ish silver 
    };

    Dielectric mat_glass{1.45};
    */

    // image properties
    const int img_width = vga_scr.PIXEL_WIDTH;
    const int img_height = vga_scr.PIXEL_HEIGHT;
    const int max_ray_recursion_depth = 50;
    const int samples_per_pixel = 20;

    Lambertian mat_ground{Color(0.15, 0.37, 0.03)};
    Lambertian mat_center{Color(0.1, 0.2, 0.8)};

    Sphere ground{Point3(0.0, -100.5, -1.0), 100.0, &mat_ground};
    
    HittableList scene;
    scene.add(ground);

    for (int i = 0; i < sphere_count; i++)
    {
        /*
        int mat_type = random.random_double(0.0, 10.0);
        Material* mat;

        if (mat_type <= 2) {
            mat = &mat_glass;
        } else if (mat_type <= 6) {
            mat = &metals[0];
        } else mat = &diffuse_mats[0];
        */
        // Sphere s { sphere_origins[i], 0.08, mat };

        Sphere s { sphere_origins[i], 0.06, &mat_center };
        spheres[i] = s;
        scene.add(spheres[i]);
    }

    Camera camera;

    // rendering
    for (int j = img_height - 1; j >= 0; --j) {
        for (int i = 0; i < img_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int n = 0; n < samples_per_pixel; ++n) {
                auto u = (i + random.random_double()) / (img_width - 1);
                auto v = (j + random.random_double()) / (img_height - 1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, scene, max_ray_recursion_depth);
            }
            write_pixel(pixel_color, samples_per_pixel);
        }
    }
}

void Raytracer::erase() {
    vga_scr.fill(0x00); // fill black
}

Raytracer raytracer{};