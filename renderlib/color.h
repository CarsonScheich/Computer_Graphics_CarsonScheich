#pragma once
#include "vec3.h"

#include <cmath>
#include <iostream>
#include <algorithm>



class color : public vec3 {
    public:
    double e[3];

    color();

    color(double e0, double e1, double e2);

    static color clamp_color(const vec3& c);

//This writes out the 0-1 color into a png output of 0-256
  void write_color(std::ostream& out, const vec3& pixel_color);


};

