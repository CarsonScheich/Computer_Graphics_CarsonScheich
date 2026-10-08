#ifndef LAMBERTIAN_SAHDER_H
#define LAMBERTIAN_SAHDER_H

#include "Shader.h"
#include "Light.h"
#include "../vec3.h"
#include "../color.h"
#include "../Shapes/Hittable.h"
#include "../Shapes/Hittable_list.h"



class Lambertian : public Shader {
    public:
    Lambertian(Light light) : light(light) {
        }

     color raycolor(const HitRecord& rec) const override {

    vec3 light_dir =
        unit_vector(light.getPosition() - rec.p);
    double diffuse =
        std::max(0.0, dot(rec.normal, light_dir));
    return color::clamp_color(rec.hit_color * diffuse);

}

    private:   
        Light light;

    };


#endif