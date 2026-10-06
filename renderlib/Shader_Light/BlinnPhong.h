#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "Shader.h"
#include "vec3.h"
#include "Light.h"
#include "PerspectiveCamera.h"
#include <algorithm>


class BlinnPhong : public Shader{
    public:

    BlinnPhong(Light light, Perspective camera) : light(light), camera_position(camera.getposition()){};

    color raycolor(const HitRecord& rec) const override {
        color albedo = rec.hit_color;
        vec3 light_dir = unit_vector(light.getPosition() - rec.p);
        double diffuse = std::max(0.0, dot(rec.normal,light_dir));

        color labertianComponent = albedo * diffuse;

        vec3 view_dir = unit_vector(camera_position - rec.p);

        vec3 halfway = unit_vector(light_dir + view_dir);
        double specularComponent = std::pow(std::max(0.0, dot(rec.normal,halfway)),phongExp);

        //return albedo * diffuse + color(1.0,1.0,1.0) * (.2 *specular);
        color shaded = labertianComponent + color(1.0,1.0,1.0) * specularComponent;
return color(
    std::clamp(shaded.x(), 0.0, 1.0),
    std::clamp(shaded.y(), 0.0, 1.0),
    std::clamp(shaded.z(), 0.0, 1.0)
);

    }

    private:
        Light light;
        double phongExp = 32 ;
        vec3 camera_position;

};

#endif