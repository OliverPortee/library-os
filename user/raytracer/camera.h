
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vec3.h"
#include "ray.h"

class Camera {
   public:
    Camera();

    Ray get_ray(double y, double x) const;

   private:
    Point3 origin;
    Point3 lower_left;
    Vec3 horizontal;
    Vec3 vertical;
};

#endif