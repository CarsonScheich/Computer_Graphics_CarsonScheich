#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Hittable.h"




class Triangle : public Shape {
    public: 
    Triangle(const point3 alpha, const point3 beta, const point3 gamma, color col, std::shared_ptr<Shader> shade) 
    : alpha(alpha), beta(beta), gamma(gamma), Triangle_color(col), shader(shade){}
    
    bool hit(double t_min, double t_max, const ray& r, HitRecord& rec) const override{
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
        double l = alpha.z() - r.origin().z();

        rec.normal = unit_vector(cross(beta - alpha, gamma - alpha));

        double M = a * (e*i - h*f) + b* (g*f - d*i) + c * (d*h - e*g);
        // deviding by 0 is undefined and this case can be thrown out
         if (M == 0) {            
            return false;
         }

        double t = -(f * (a*k - j*b) + e * (j*c - a*l)+ d * (b*l - k*c)) / M;


         if (t < t_min || t> t_max) {
            return false;
         }

         double gamma_val = (i * (a*k - j*b) + h * (j*c - a*l) + g*(b*l - k*c))/ M;

         if (gamma_val < 0 || gamma_val > 1 ) {
            return false;
         }

         double beta_val = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g))/ M;

         if (beta_val < 0 || beta_val > 1 - gamma_val) {
            return false;
         }
         rec.hit_color = Triangle_color;
         rec.p = r.at(t);
         rec.t = t;
         rec.shader = shader;
         return true;

    }



    private:
    point3 alpha, beta, gamma;
    color Triangle_color;
    std::shared_ptr<Shader> shader;
// a d g alpha
//b e h beta
//c f i. gamma



};

#endif 