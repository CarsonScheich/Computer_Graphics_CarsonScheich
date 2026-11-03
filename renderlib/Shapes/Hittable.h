#ifndef HITTABLE_H
#define HITTABLE_H


#include <cmath>
#include "../ray.h"
#include "../vec3.h"
#include "../color.h"
#include "../AABB.h"
#include <memory>
#include <vector>

class Shader;

struct HitRecord {
    point3 p;
    vec3 normal;
    double t; //smaller means closer
    color hit_color = color(.5,.5,.5);
    std::shared_ptr<Shader> shader;
    bool front_face;

};

using std::make_shared;
using std::shared_ptr;

class Shape {
public:
    virtual ~Shape() = default;
    Shape() = default;;

    virtual bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const = 0;
    virtual AABB bounding_box() const = 0;

};


#endif
