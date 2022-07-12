#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "library/random.h"
#include "machine/cpu.h"
#include "machine/vgascr.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"
#include "user/raytracer/camera.h"
#include "user/raytracer/hittable_list.h"
#include "user/raytracer/ray.h"
#include "user/raytracer/sphere.h"
#include "user/raytracer/utility.h"
#include "user/raytracer/colour.h"
// #include "user/raytracer/material.h"

void test_scr() {
    // step through with gdb
    for (unsigned char i = 0; i < 5; i++) {
        vga_scr.fill(i);
        // 0: black
        // 1: blue
        // 2: green
        // 3: cyan
        // 4: red
    }

    struct byte_colour light_blue {
        0x00, 0x1c, 0x71
    };
    vga_scr.fill(vga_scr.match_colour(light_blue));
}

Color ray_color(const Ray& ray, /*const?*/ Hittable& scene, int depth) {
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

void render() {
    // image properties
    const int img_width = vga_scr.PIXEL_WIDTH;
    const int img_height = vga_scr.PIXEL_HEIGHT;
    const int max_ray_recursion_depth = 50;
    const int samples_per_pixel = 20;

    Lambertian mat_ground{Color(0.8, 0.8, 0)};
    Lambertian mat_center{Color(0.1, 0.2, 0.5)};
    Metal mat_right{Color(0.8, 0.6, 0.2), 0.5};
    Dielectric mat_glass{1.45};

    Sphere left{Point3(-1, 0, -1), 0.5, &mat_glass};
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

int main() {
    Secure secure;
    cpu.enable_int();
    keyboard.plugin();
    // watch.windup();

    // organizer.Organizer::ready(app);
    // organizer.Scheduler::schedule();

    // test_scr();
    render();
    cpu.halt();

    return 0;
}