#ifndef LAMBERTIAN_SAHDER_H
#define LAMBERTIAN_SAHDER_H

#include "Shader.h"
#include "Light.h"
#include "../vec3.h"
#include "../color.h"
#include <algorithm>



class Lambertian : public Shader {
    public:
    Lambertian() = default;

    color raycolor(const HitRecord& rec, const Light& light) const override {
        vec3 light_dir = unit_vector(light.getPosition() - rec.p);
        float diffuse = std::max(0.0, dot(rec.normal, light_dir));

        color result = rec.hit_color * light.getIntensity() * diffuse;

        return color::clamp_color(result);
}

    private:   
        std::vector<std::shared_ptr<Light>> lights;

    };


#endif