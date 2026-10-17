#ifndef BOX_H
#define BOX_H

#include "Hittable.h"
#include "Triangle.h"
#include "Rectangle.h"

class Box : public Shape {
    public:
    Box(const point3& minCorner, const point3& maxCorner, color col, std::shared_ptr<Shader> shade){
            double x0 = minCorner.x();
            double y0 = minCorner.y();
            double z0 = minCorner.z();

            double x1 = maxCorner.x();
            double y1 = maxCorner.y();
            double z1 = maxCorner.z();

            faces.emplace_back(point3(x0,y0,z1), point3(x1,y0,z1), point3(x0,y1,z1),point3(x1,y1,z1),col,shade);

            faces.emplace_back(point3(x1,y0,z0), point3(x0,y0,z0), point3(x1,y1,z0),point3(x0,y1,z0),col,shade);

            faces.emplace_back(point3(x0,y0,z0), point3(x0,y0,z1), point3(x0,y1,z0),point3(x0,y1,z1),col,shade);

            faces.emplace_back(point3(x1,y0,z1), point3(x1,y0,z0), point3(x1,y1,z1),point3(x1,y1,z0),col,shade);

            faces.emplace_back(point3(x0,y1,z1), point3(x1,y1,z1), point3(x0,y1,z0),point3(x1,y1,z0),col,shade);

            faces.emplace_back(point3(x0,y0,z0), point3(x1,y0,z0), point3(x0,y0,z1),point3(x1,y0,z1),col,shade);
    }

    bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override {
        bool hitAnything = false;
        double closest = t_max;

        for (const auto& face :faces){
            if (face.hit(t_min,closest,r,rec)){
                hitAnything = true;
                closest = rec.t;
            }
        }
        return hitAnything;
    }

    private:
        std::vector<Rectangle> faces;

};

#endif