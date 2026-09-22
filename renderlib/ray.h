#ifndef RAY_H
#define RAY_H

#include "vec3.h"

//REMINDER FOR SELF
//
// vec3 and point3 are both vec3 classes. This is just for grammer. We start at a point 
// and then that point has a direction

class ray {
    public:

        ray() {} // Creating a empty ray

        ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {} // ray with direction

        const point3& origin() const {return orig; } //getting the origin from priv
        const vec3& direction() const { return dir; } //getting the direction from priv

        point3 at(double t) const {
            return orig + t * dir;
        }


     private:
        point3 orig;
        vec3 dir;

};

#endif 