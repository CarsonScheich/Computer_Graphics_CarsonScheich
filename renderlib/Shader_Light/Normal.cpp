#include "Normal.h"

NormalShader::NormalShader() {}


color NormalShader::raycolor(const HitRecord &hit) const {
vec3 n = 0.5 * (hit.normal + vec3(1.0,1.0,1.0));

return color(n.x(), n.y(), n.z());
}