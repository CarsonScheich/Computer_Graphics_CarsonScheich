#ifndef SQUARE_H
#define SQUARE_H

#include "Hittable.h"
#include "Triangle.h"
#include "color.h"
#include <vector>


class Square: Shape{
    public:

    Square(const point3 alpha, const point3 beta, const point3 gamma, color col, std::shared_ptr<Shader> shade){

        point3 closeleftcorner;
        //This one be one side of the Square
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);

        //This is side 2
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);

        //This is side 3
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        Triangle(alpha, beta, gamma, col, shade);

        //This is side 4
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);

        //This is side 5
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);

        //This is side 6
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);
        List_tringles.emplace_back(alpha, beta, gamma, col, shade);

    }

    bool hit(double t_min, double t_max, const ray& r, HitRecord rec) const {


    }


    private:
    point3 alpha, beta, gamma;
    color Square_color;
    std::shared_ptr<Shader> shader;
    std::vector<Triangle> List_tringles;


};


#endif