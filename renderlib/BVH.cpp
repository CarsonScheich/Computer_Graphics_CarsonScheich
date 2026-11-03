#include "BVH.h"
#include <algorithm>
#include <stdexcept>


BVHNode::BVHNode(std::vector<std::shared_ptr<Shape>> objects, int axis)
    : bbox(point3(0, 0, 0), point3(0, 0, 0)) {

    if (objects.empty()) {
        throw std::invalid_argument("Cannot build a BVH from an empty list");
    }

    std::sort(objects.begin(), objects.end(), [axis](const auto& a, const auto& b) {
        AABB boxA = a->bounding_box();
        AABB boxB = b->bounding_box();

        if (axis == 0) return boxA.minimum.x() < boxB.minimum.x();
        if (axis == 1) return boxA.minimum.y() < boxB.minimum.y();
        return boxA.minimum.z() < boxB.minimum.z();
    });

    if (objects.size() == 1) {
        left = objects[0];
        right = nullptr;
        bbox = left->bounding_box();
        return;
    }

    size_t mid = objects.size() / 2;

    std::vector<std::shared_ptr<Shape>> leftObjects(
        objects.begin(), objects.begin() + mid
    );

    std::vector<std::shared_ptr<Shape>> rightObjects(
        objects.begin() + mid, objects.end()
    );

    if (leftObjects.size() == 1)
        left = leftObjects[0];
    else
        left = std::make_shared<BVHNode>(leftObjects, (axis + 1) % 3);

    if (rightObjects.size() == 1)
        right = rightObjects[0];
    else
        right = std::make_shared<BVHNode>(rightObjects, (axis + 1) % 3);

    AABB box1 = left->bounding_box();
    AABB box2 = right->bounding_box();

    point3 minimum(
        std::min(box1.minimum.x(), box2.minimum.x()),
        std::min(box1.minimum.y(), box2.minimum.y()),
        std::min(box1.minimum.z(), box2.minimum.z())
    );
    point3 maximum(
        std::max(box1.maximum.x(), box2.maximum.x()),
        std::max(box1.maximum.y(), box2.maximum.y()),
        std::max(box1.maximum.z(), box2.maximum.z())
    );

    bbox = AABB(minimum, maximum);
}

bool BVHNode::hit(double tmin, double tmax, const ray& r, HitRecord& rec ) const {

    if (!bbox.hit(tmin, tmax, r)) {
        return false;
    }

    HitRecord leftRec;
    HitRecord rightRec;

    bool hitLeft = left &&
        left->hit(tmin, tmax,r, leftRec);

    bool hitRight = right && right->hit(tmin, hitLeft ? leftRec.t : tmax, r, rightRec);

    if (hitRight) {
        rec = rightRec;
        return true;
    }

    if (hitLeft) {
        rec = leftRec;
        return true;
    }

    return false;
}

