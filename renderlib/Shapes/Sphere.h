#ifndef SPHERE_H
#define SPHERE_H

#include "../vec3.h"
#include "../ray.h"
#include "Hittable.h"
#include "../color.h"
#include "../Shader_Light/Shader.h"
#include "../AABB.h"
#include "../BVH.h"

#include <array>
#include <vector>

using std::make_shared;
using std::shared_ptr;


class Sphere : public Shape {
    public:

    Sphere(const point3& center, double radius, color col, std::shared_ptr<Shader> shade) 
    : center(center), radius(std::fmax(0,radius)), Sphere_color(col), shader(shade){}

    AABB bounding_box() const override {
    vec3 radiusVec(radius, radius, radius);
    return AABB(
        center - radiusVec,
        center + radiusVec
    );

}


    bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override {

    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrt_discriminant = std::sqrt(discriminant);
    double t = (-b - sqrt_discriminant) / (2.0 * a);
    if (t < t_min || t > t_max) {
        t = (-b + sqrt_discriminant) / (2.0 * a);
        if (t < t_min || t > t_max) {
            return false;
        }

    }

    rec.t = t;
    rec.p = r.at(t);
    rec.normal = (rec.p - center) / radius;
    rec.hit_color = Sphere_color;
    rec.shader = shader;
    return true;
}


    //CODE mainly for OpenGL

    
    std::vector<float> getOpenGLVertices(int subdivisions = 3) const override{
        const double t = (1.0 + std::sqrt(5.0)) / 2.0;

        std::array<point3, 12> vertices{
            point3(-1, t, 0), point3(1, t, 0),
            point3(-1, -t, 0), point3(1, -t, 0),
            point3(0, -1, t), point3(0, 1, t),
            point3(0 , -1, -t), point3(0, 1, -t),
            point3(t, 0, -1), point3(t, 0, 1),
            point3(-t, 0, -1), point3(-t, 0, 1)
        };

        for (auto& vertex : vertices){
            vertex = unit_vector(vertex);
        }

        const int faces[20][3]{
        {0,11,5}, {0,5,1},  {0,1,7},  {0,7,10}, {0,10,11},
        {1,5,9},  {5,11,4}, {11,10,2},{10,7,6}, {7,1,8},
        {3,9,4},  {3,4,2},  {3,2,6},  {3,6,8},  {3,8,9},
        {4,9,5},  {2,4,11}, {6,2,10}, {8,6,7},  {9,8,1}
        };

        std::vector<float> buffer;
         for (const auto& face : faces) {
        subdivide(
            vertices[face[0]],
            vertices[face[1]],
            vertices[face[2]],
            subdivisions,
            buffer
        );
        }

        return buffer;
    }

    private:
        point3 center;
        double radius;
        color Sphere_color;
        std::shared_ptr<Shader> shader;

        void subdivide(const vec3& a, const vec3& b, const vec3& c,
               int depth, std::vector<float>& buffer) const {
        if (depth == 0) {
            addVertex(a, buffer);
            addVertex(b, buffer);
            addVertex(c, buffer);
            return;
        }

        vec3 ab = unit_vector((a + b) / 2.0);
        vec3 bc = unit_vector((b + c) / 2.0);
        vec3 ca = unit_vector((c + a) / 2.0);

        subdivide(a, ab, ca, depth - 1, buffer);
        subdivide(ab, b, bc, depth - 1, buffer);
        subdivide(ca, bc, c, depth - 1, buffer);
        subdivide(ab, bc, ca, depth - 1, buffer);
    }

    void addVertex(const vec3& normal,
               std::vector<float>& buffer) const {
        point3 position = center + radius * normal;

        // Position
        buffer.push_back(static_cast<float>(position.x()));
        buffer.push_back(static_cast<float>(position.y()));
        buffer.push_back(static_cast<float>(position.z()));

        // Normal
        buffer.push_back(static_cast<float>(normal.x()));
        buffer.push_back(static_cast<float>(normal.y()));
        buffer.push_back(static_cast<float>(normal.z()));
    }

};


#endif