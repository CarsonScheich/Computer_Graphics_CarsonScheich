#pragma once
#include "vec3.h"

#include <cmath>
#include <iostream>
#include <algorithm>



class color : public vec3 {
    public:
    
    color();

    color(double e0, double e1, double e2);
    color(const vec3& v) : vec3(v) {}

    static color clamp_color(const vec3& c);

//This writes out the 0-1 color into a png output of 0-256
  void write_color(std::ostream& out, const vec3& pixel_color);

        color operator-() const { return color(-e[0], -e[1], -e[2]); }
        double operator[] (int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        color& operator+=(const color& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        color& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        color& operator/=(double t) {
            return *this *= 1/t;
        }

        double length() const {
            return std::sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] +e[2]*e[2];
        }

};

 inline std::ostream& operator<<(std::ostream& out, const color v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
 }

inline color operator+(const color& u, const color& v) {
    return color(u.e[0] + v.e[0], u.e[1] + v.e[1], + u.e[2] + v.e[2]);
 }

 inline color operator+(const color& c, const vec3& v) {
    return color( c[0] + v[0], c[1] + v[1], c[2] + v[2]);
}

 inline color operator-(const color& u, const color& v) {
    return color(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
 }

inline color operator*(double t, const color& v) {
    return color(t*v.e[0], t*v.e[1], t*v.e[2]);
}

 inline color operator*(const color& v, double t) {
    return t * v;
 }

inline color operator/(const color& v, double t) {
    return (1/t) * v;
 }

 inline color operator*(const color& u, const color& v) {
    return color(
        u[0] * v[0],
        u[1] * v[1],
        u[2] * v[2]
    );
}

 inline double dot(const color& u, const color& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
 }

 inline color cross (const color& u, const color& v) {
    return color(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
 }

 inline color unit_vector(const color& v) {
        return v / v.length();
 }

