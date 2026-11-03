#ifndef BLINNPHONG_H
#define BLINNPHONG_H

#include "Shader.h"
#include "../vec3.h"
#include "Light.h"
#include "../color.h"
#include "../Cameras/PerspectiveCamera.h"
#include "../Scene.h"
#include <algorithm>
#include <vector>
#include <memory>


class BlinnPhong : public Shader{
    public:

    BlinnPhong(Perspective camera, double phongExp) : camera_position(camera.getposition()), phongExp(phongExp) {};

    color raycolor(const HitRecord& rec, const Light& light) const override {
        color shaded(0,0,0);
        color albedo = color::clamp_color(rec.hit_color);

        vec3 view_dir = unit_vector(camera_position - rec.p);
        vec3 light_dir = unit_vector(light.getPosition() - rec.p);

        double diffuse = std::max(0.0, dot(rec.normal,light_dir));
        color intensity = light.getIntensity();

        shaded += (albedo * intensity) * diffuse;
        if (diffuse > 0.0) {
            vec3 halfway = unit_vector(light_dir + view_dir);
            double specularComponent = std::pow(std::max(0.0, dot(rec.normal,halfway)),phongExp);
            shaded += intensity * specularComponent;
        }

        return color::clamp_color(shaded);

    }

    private:
        double phongExp = 32 ;
        vec3 camera_position;

};

#endif