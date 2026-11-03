#ifndef SHADER_H
#define SHADER_H

#include "../vec3.h"
#include "../Shapes/Hittable.h"
#include "color.h"
#include "Light.h"


class Shader {
    public:
    virtual ~Shader() = default;

    virtual bool needsLighting() const {
    return true;
    }

    virtual color raycolor(const HitRecord& rec, const Light& light) const {
        return raycolor(rec);
    }

        virtual color raycolor(const HitRecord& rec) const {
        return color::clamp_color(.5 * (rec.normal + vec3(1.0, 1.0, 1.0))
        );

    }

    virtual bool reflectedRay(
    const ray& incoming, const HitRecord& rec, ray& reflected) const {
    return false;
    }


};




#endif 