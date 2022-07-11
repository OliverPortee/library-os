
#include "hittable_list.h"

void HittableList::add(Hittable& hittable) {
    assert(size < MAX_HITTABLES, "more than MAX_HITTABLES hittables");
    hittables[size++] = &hittable;
}

void HittableList::clear() { size = 0; }

bool HittableList::hit(const Ray& ray, double t_min, double t_max,
                       HitInfo& out_hitinfo) {
    HitInfo tmp;
    bool hit_something = false;
    double t_closest = t_max;
    for (unsigned int i = 0; i < size; ++i) {
        Hittable* h = hittables[i];
        if (h->hit(ray, t_min, t_closest, tmp)) {
            hit_something = true;
            t_closest = tmp.t;
            out_hitinfo = tmp;
        }
    }
    return hit_something;
}