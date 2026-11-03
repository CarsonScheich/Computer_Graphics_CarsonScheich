#include "BVH.h"

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