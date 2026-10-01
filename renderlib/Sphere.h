#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "Hittable.h"


class Sphere : public Shape {
    public:

    Sphere(const point3& center, double radius, color col) : center(center), radius(std::fmax(0,radius)) {}


bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override {

    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrt_discriminant = std::sqrt(discriminant);
    double t = (-b - sqrt_discriminant) / (2.0 * a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_discriminant) / (2.0 * a);
        if (t < t_min || t > t_max) {
            return false;
        }

    }

    rec.t = t;
    rec.p = r.at(t);
    rec.normal = (rec.p - center) / radius;
    rec.hit_color = Sphere_color;
    return true;
}


    private:
        point3 center;
        double radius;
        color Sphere_color;

};


#endif