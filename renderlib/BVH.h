#ifndef BVH_H
#define BVH_H

#include "Shapes/Hittable.h"
#include "AABB.h"



class BVHNode : public Shape {
private:
    std::shared_ptr<Shape> left;
    std::shared_ptr<Shape> right;

    AABB bbox;

public:
    BVHNode(
        std::vector<std::shared_ptr<Shape>> objects,
        int axis
    );

    bool hit(double tmin, double tmax, const ray& r, HitRecord& rec) const override;

    
    AABB bounding_box() const override {
        return bbox;
    }
};

#endif