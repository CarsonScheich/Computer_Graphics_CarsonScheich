#ifndef LIGHT_H
#define LIGHT_H

#include "../vec3.h"

class Light {
    public:
    Light(const point3& position, const color& intensity = color(1,1,1))
    : position(position) , intensity(intensity){}

    point3 getPosition() const {
        return position;
    }

    color getIntensity() const {
        return intensity;
    }
    
    private:
    point3 position;
    color intensity;

};

#endif