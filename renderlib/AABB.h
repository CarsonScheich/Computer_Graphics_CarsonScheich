#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "ray.h"
#include <algorithm>

class AABB {
public:
    AABB() = default;

    point3 minimum;
    point3 maximum;

    AABB(point3 min, point3 max) : minimum(min), maximum(max) {}

    bool hit(double tmin, double tmax, const ray& r) const {
    const point3 origin = r.origin();
    const vec3 direction = r.direction();

    const double o[3] = {origin.x(), origin.y(), origin.z()};
    const double d[3] = {direction.x(), direction.y(), direction.z()};

    const double lo[3] = {minimum.x(), minimum.y(), minimum.z()};
    const double hi[3] = {maximum.x(), maximum.y(), maximum.z()};

    for (int axis = 0; axis < 3; ++axis) {
        if (d[axis] == 0.0) {
            if (o[axis] < lo[axis] || o[axis] > hi[axis])
                return false;
            continue;
        }

        double t0 = (lo[axis] - o[axis]) / d[axis];
        double t1 = (hi[axis] - o[axis]) / d[axis];

        if (t0 > t1)
            std::swap(t0, t1);

        tmin = std::max(tmin, t0);
        tmax = std::min(tmax, t1);

        if (tmax < tmin)
            return false;
    }
    return true;
}
};

#endif