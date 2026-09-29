#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "Hittable.h"


class Sphere : public Shape {
    public:
    Sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}


    bool hit(double t_min, double t_max, const ray& r, HitRecord rec) const override{
                vec3 oc = center - r.origin();
        auto a = dot(r.direction(), r.direction());
        auto b = -2.0 * dot(r.direction(), oc);
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        return (discriminant >= 0);
    } // THIS SHOULD LATER BE MOVED TO SHAPE AND VIRTUAL

    private:
        point3 center;
        double radius;

};


class Triangle : public Shape {
    public: 
    Triangle(const point3 alpha, const point3 beta, const point3 gamma) : alpha(alpha), beta(beta), gamma(gamma) {}
    
    bool hit(double t_min, double t_max, const ray& r, HitRecord rec) const override{
        double a = alpha.x() - beta.x();
        double b = alpha.y() - beta.y();
        double c = alpha.z() - beta.z();

        double d = alpha.x() - gamma.x();
        double e = alpha.y() - gamma.y();
        double f = alpha.z() - gamma.z();

        double g = r.direction().x();
        double h = r.direction().y();
        double i = r.direction().z();

        double j = alpha.x() - r.origin().x();
        double k = alpha.y() - r.origin().y();
        double l = alpha.z() - r.direction().z();


        double M = a * (e*i - h*f) + b* (g*f - d*i) + c * (d*h - e*g);
        // deviding by 0 is undefined and this case can be thrown out
         if (M == 0) {            
            return false;
         }

        double t = -(f * (a*k - j*b) + e * (j*c - a*l)+ d * (b*l - k*c)) / M;

         if (t < t_min || t> t_max) {
            return false;
         }

         double gamma_val = (i * (a*k - j*b) + h * (j*c -a*l) + g*(b*l - k*c)/M);

         if (gamma_val < 0 || gamma_val > 1 ) {
            return false;
         }

         double beta_val = (j * (e*i - h*f) + k * (g*f + d*i) + l * (d*h - e*g)/M);

         if (beta_val < 0 || beta_val > 1) {
            return false;
         }

         return true;

    }


    private:
    point3 alpha, beta, gamma;
// a d g alpha
//b e h beta
//c f i. gamma



};


#endif