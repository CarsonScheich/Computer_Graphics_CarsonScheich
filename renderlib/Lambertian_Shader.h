#ifndef LAMBERTIAN_SAHDER_H
#define LAMBERTIAN_SAHDER_H

#include "Shader.h"
#include "vec3.h"
#include "Hittable.h"
#include "Hittable_list.h"
#include "Light.h"


class Lambertian : public Shader {
    public:
    Lambertian(Light light) : light(light) {
        }

     color raycolor(const HitRecord& rec) const override {

    vec3 light_dir =
        unit_vector(light.getPosition() - rec.p);
    double diffuse =
        std::max(0.0, dot(rec.normal, light_dir));
    return rec.hit_color * diffuse;

}

    private:   
        Light light;

    };


#endif