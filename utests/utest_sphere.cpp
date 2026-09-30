#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Sphere.h"
#include "ray.h"
#include "vec3.h"

TEST_CASE("RAY HITS SPHERE") {

    Sphere sphere(point3(0, 0, -5), 1.0);
    ray r(
        point3(0, 0, 0),
        vec3(0, 0, -1)
    );
    HitRecord rec;
    REQUIRE(sphere.hit(0.001, 1000.0, r, rec) == true);
}

TEST_CASE("RAY MISSES SPHERE") {

    Sphere sphere(point3(0, 0, -5), 1.0);
    ray r(
        point3(0, 0, 0),
        vec3(0, 1, 0)
    );
    HitRecord rec;
    REQUIRE(sphere.hit(0.001, 1000.0, r, rec) == false);
}