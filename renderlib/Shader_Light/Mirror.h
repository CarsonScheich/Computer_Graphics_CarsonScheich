#ifndef MIRROR_H
#define MIRROR_H

#include "Shader.h"

class Mirror : public Shader{
public:

static vec3 reflect(const vec3& incomingDirection, const vec3& normal){
    vec3 n = unit_vector(normal);
    return incomingDirection - 2.0 * dot(incomingDirection, n) * n;
}

bool reflectedRay(
    const ray& incoming, const HitRecord& rec, ray& reflected) const override {

    vec3 direction = reflect(incoming.direction(), rec.normal);

    reflected = ray(rec.p + 0.001 * unit_vector(direction), direction);
    return true;
}

};

#endif 