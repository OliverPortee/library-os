
#include "camera.h"

#include "machine/vgascr.h"

Camera::Camera() {
    const double aspect_ratio = vga_scr.ASPECT_RATIO;

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;

    origin = Point3(0, 0, 0);                 // position of the camera
    horizontal = Vec3(viewport_width, 0, 0);  // x axis
    vertical = Vec3(0, viewport_height, 0);   // y axis
    lower_left = origin - horizontal / 2      // half a screen left
                 - vertical / 2               // half a screen down
                 - Vec3(0, 0, 1);  // one focal length away from the camera
}

Ray Camera::get_ray(double y, double x) const {
    return Ray(origin, lower_left + y * horizontal + x * vertical - origin);
}