#include "Scene.h"

bool Scene::isInShadow(const ray& shadowRay, const shape_list& shapes) {
    HitRecord shadowRec;

    return shapes.hit(0.001, 0.999, shadowRay, shadowRec);
}


color Scene::ray_color(const ray& r, int depth) {

    if (depth <= 0)
        return color(0, 0, 0);

    HitRecord rec;

    if (shapes.hit(0.001, 1000.0, r, rec)) {
        ray reflected;
        if (rec.shader->reflectedRay(r, rec, reflected)) {
            return ray_color(reflected, depth - 1);
        }
        if (!rec.shader->needsLighting()) {
        return rec.shader->raycolor(rec);
        }
        if (lights.empty()) {
            return color(0,0,0);
        }
        color finalColor = rec.hit_color * 0.05;
        for (const auto& light : lights){
        point3 shadowOrigin = rec.p + rec.normal * 0.001;
        vec3 toLight = light->getPosition() - shadowOrigin;
        ray shadowRay(shadowOrigin, toLight);

        if (!isInShadow(shadowRay, shapes)) {
        finalColor += rec.shader->raycolor(rec, *light);
        }
    }
       return color::clamp_color(finalColor);
    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);

    return color(
        (1.0 - t) * 0.01 + t * 0.5,
        (1.0 - t) * 0.01 + t * 0.7,
        (1.0 - t) * 0.08 + t * 1
    );
}