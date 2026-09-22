#include "Sphere.h"

class Sphere{

    bool hit(const point3& center, double radius, const ray& r) {
        vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    }

    
};