#ifndef HITTABLE_H
#define HITTABLE_H


#include <cmath>
#include "ray.h"
#include "vec3.h"

struct HitRecord {


    point3 p;
    vec3 normal;
    double t; //smaller means closer



};


class Shape {
public:

    virtual bool hit(double t_min, double t_max, const ray& r, HitRecord rec) const = 0;

    virtual bool intersect( const ray &r, const float tmin, float &tmax ) = 0;



};




#endif
