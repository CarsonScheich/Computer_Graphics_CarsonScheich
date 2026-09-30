#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "Hittable.h"


class Sphere : public Shape {
    public:
    
    Sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}


    bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override{
                vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    } // THIS SHOULD LATER BE MOVED TO SHAPE AND VIRTUAL

    private:
        point3 center;
        double radius;

};


#endif