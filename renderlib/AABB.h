#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "ray.h"

class AABB {
public:
    point3 minimum;
    point3 maximum;

    AABB(point3 min, point3 max) : minimum(min), maximum(max) {}

    bool hit(double tmin, double tmax, const ray& r) const;
};

#endif