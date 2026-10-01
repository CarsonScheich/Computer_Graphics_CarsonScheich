#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;


class shape_list : public Shape {
public:
    std::vector<shared_ptr<Shape>> objects;

    shape_list() {}
    shape_list(shared_ptr<Shape> object) { add(object); }

    void clear() {objects.clear(); }

    void add(shared_ptr<Shape> object){
        objects.push_back(object);
    }

        bool hit(double ray_tmin, double ray_tmax, const ray& r, HitRecord& rec) const override {
        HitRecord temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(ray_tmin, closest_so_far, r , temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }




};

#endif