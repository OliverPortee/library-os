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
#include "user/raytracer/colour.h"
#include "user/raytracer/hittable_list.h"
#include "user/raytracer/ray.h"
#include "user/raytracer/sphere.h"
#include "user/raytracer/utility.h"
#include "user/raytracer/vec3.h"

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

Color ray_color(const Ray& ray, /*const?*/ Hittable& scene) {
    HitInfo hit_info;
    if (scene.hit(ray, 0, INFINITY, hit_info)) {
        return 0.5 * (hit_info.normal + Color(1.0, 1.0, 1.0));
    }

    Vec3 unit_dir = ray.direction.normalized();
    auto t = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.0, 0.0, 0.0);
}

void render() {
    // image properties
    const int img_width = vga_scr.PIXEL_WIDTH;
    const int img_height = vga_scr.PIXEL_HEIGHT;
    const int samples_per_pixel = 100;

    // scene (list of 3D objects)
    HittableList scene;
    Sphere s = Sphere(Point3(0.0, 0.0, -1.0), 0.5);
    Sphere ground = Sphere(Point3(0.0, 100.5, -1.0), 100.0);
    scene.add(s);

    Camera camera;

    // rendering
    for (int j = img_height - 1; j >= 0; --j) {
        for (int i = 0; i < img_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int n = 0; n < samples_per_pixel; ++n) {
                auto u = (i + random.random_double()) / (img_width - 1);
                auto v = (j + random.random_double()) / (img_height - 1);
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, scene);
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

    //organizer.Organizer::ready(app);
    //organizer.Scheduler::schedule();
    
    // test_scr();
    render();
    cpu.halt();

    return 0;
}