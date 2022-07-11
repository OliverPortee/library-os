#include "device/keyboard.h"
#include "device/watch.h"
#include "guard/secure.h"
#include "machine/cpu.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_organizer.h"
#include "user/appl.h"
#include "machine/vgascr.h"
#include "user/raytracer/utility.h"
#include "user/raytracer/vec3.h"
#include "user/raytracer/ray.h"
#include "user/raytracer/colour.h"
#include "user/raytracer/hittable_list.h"
#include "user/raytracer/sphere.h"

void test_scr() {
    // step through with gdb
    for (unsigned char i = 0; i < 5; i++)
    {
        vga_scr.fill(i);
        // 0: black
        // 1: blue
        // 2: green
        // 3: cyan
        // 4: red
    }

    struct byte_colour light_blue { 0x00, 0x1c, 0x71 };
    vga_scr.fill(vga_scr.match_colour(light_blue));
}

colour ray_colour(const Ray& ray, /*const?*/ Hittable& scene) {
    HitInfo hit_info;
    if (scene.hit(ray, 0, INFINITY, hit_info)) {
        return 0.5 * (hit_info.normal + colour(1.0, 1.0, 1.0));
    } 

    Vec3 unit_dir = ray.direction.normalized();
    auto t = 0.5*(unit_dir.y + 1.0);
    return (1.0-t) * colour(1.0, 1.0, 1.0) 
               + t * colour(0.0, 0.0, 0.0);
}

void render() {
    // image properties
    const auto aspect_ratio = vga_scr.ASPECT_RATIO;
    const int img_width = vga_scr.PIXEL_WIDTH;
    const int img_height = vga_scr.PIXEL_HEIGHT;

    // scene (list of 3D objects)
    HittableList scene;
    Sphere s = Sphere(Point3(0.0, 0.0, -1.0), 0.5);
    Sphere ground = Sphere(Point3(0.0, 100.5, -1.0), 100.0); 
    scene.add(s);

    // camera setup 
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    Point3 cam_origin = Point3(0,0,0);              // position of the camera
    Vec3 horizontal = Vec3(viewport_width, 0, 0);   // x axis
    Vec3 vertical = Vec3(0, viewport_height, 0);    // y axis
    Vec3 lower_left = cam_origin 
                    - horizontal/2                  // half a screen left 
                    - vertical/2                    // half a screen down
                    - Vec3(0, 0, focal_length);     // one focal length away from the camera

    // rendering
    for (int j = img_height-1; j >= 0; --j)
    {
        for (int i = 0; i < img_width; ++i)
        {
            auto u = double(i) / (img_width-1);
            auto v = double(j) / (img_height-1);
            Vec3 ray_dir = lower_left               // lower left pixel of the screen   ┐   
                         + u * horizontal           // offset in x direction            │ position of the sampled point
                         + v * vertical             // offset in y direction            ┘  
                         - cam_origin;              // get vector to camera origin
            
            struct Ray r{.origin=cam_origin, .direction=ray_dir};
            colour pixel_colour = ray_colour(r, scene);
            write_pixel(pixel_colour);       
        }   
    }
}

int main() {
    Secure secure;
    cpu.enable_int();
    keyboard.plugin();
    //watch.windup();

    //organizer.Organizer::ready(app);
    //organizer.Scheduler::schedule();
    
    // test_scr();
    render();
    cpu.halt();

    return 0;
}