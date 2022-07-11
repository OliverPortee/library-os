
#ifndef __HITTABLE_LIST_H__
#define __HITTABLE_LIST_H__

#include "hittable.h"
#include "object/assert.h"

#define MAX_HITTABLES 1000

struct HittableList : Hittable {
    void add(Hittable& hittable);
    void clear();
    virtual bool hit(const Ray& ray, double t_min, double t_max,
                     HitInfo& out_hitinfo);

    Hittable* hittables[MAX_HITTABLES];
    unsigned int size = 0;
};

#endif