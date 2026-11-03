#include "color.h"


color::color() : vec3{0,0,0} {}

color::color(double e0, double e1, double e2) : vec3{e0,e1,e2}  {}


void color::write_color(std::ostream& out, const vec3& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();
    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);
    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}


    color color::clamp_color(const vec3& c) {
        return color(
        std::clamp(c.x(), 0.0, 1.0),
        std::clamp(c.y(), 0.0, 1.0),
        std::clamp(c.z(), 0.0, 1.0)
    );
}
