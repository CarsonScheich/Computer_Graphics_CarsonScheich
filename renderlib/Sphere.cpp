#include "Sphere.h"
#include "Hittable.h"


class Sphere : public Shape {


/*
    bool Sphere::hit(double t_min, double t_max, const ray& r, HitRecord) const {
        vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    }
*/


};