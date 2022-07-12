#ifndef __RT_APP_H__
#define __RT_APP_H__

#include "syscall/thread.h"
#include "user/raytracer/hittable.h"
#include "user/raytracer/ray.h"
#include "user/raytracer/vec3.h"

enum Scene {
    demo, 
    secret,
};

class Raytracer : public Thread {
   public:
    Raytracer();
    void action();
    void set_scene(Scene s);

   private:
    Scene selected_scene = demo;
    Color ray_color(const Ray& ray, /*const?*/ Hittable& scene, int depth);
    void erase();
    void render();
    void render_secret();
};



extern Raytracer raytracer;

#endif