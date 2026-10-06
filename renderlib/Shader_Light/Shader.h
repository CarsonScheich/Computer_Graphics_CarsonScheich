#ifndef SHADER_H
#define SHADER_H

#include "../vec3.h"
#include "../Shapes/Hittable.h"

class Shader {
    public:

    virtual color raycolor(const HitRecord& rec) const {
        return 0.5 * (rec.normal + vec3(1.0, 1.0, 1.0));
    }


};




#endif 