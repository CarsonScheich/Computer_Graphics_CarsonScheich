#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Hittable.h"
#include "Triangle.h"
#include "../BVH.h"
#include "../AABB.h"
#include "color.h"
#include <vector>


class Rectangle: public Shape{
    public:

    Rectangle(const point3 bottomLeft, const point3 bottomRight, const point3 topLeft, const point3 topRight, color col, std::shared_ptr<Shader> shade){
        //This one be one side of the Square
        List_tringles.emplace_back(bottomLeft, bottomRight, topLeft, col, shade);
        List_tringles.emplace_back(bottomRight, topRight, topLeft, col, shade);
        
    }

    AABB bounding_box() const override {
    AABB a = List_tringles[0].bounding_box();
    AABB b = List_tringles[1].bounding_box();

    point3 minimum(
        std::min(a.minimum.x(), b.minimum.x()),
        std::min(a.minimum.y(), b.minimum.y()),
        std::min(a.minimum.z(), b.minimum.z())
    );
    point3 maximum(
        std::max(a.maximum.x(), b.maximum.x()),
        std::max(a.maximum.y(), b.maximum.y()),
        std::max(a.maximum.z(), b.maximum.z())
    );
    return AABB(minimum, maximum);
    }
    

    bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override {
        bool hitAnything = false;
        double closest = t_max;
        
        for (const auto& triangle : List_tringles){
            if (triangle.hit(t_min, closest, r, rec)){
                hitAnything = true;
                closest = rec.t;
                
            }
        }
        return hitAnything;
    }


    private:
    point3 alpha, beta, gamma;
    color Square_color;
    std::shared_ptr<Shader> shader;
    std::vector<Triangle> List_tringles;


};


#endif
