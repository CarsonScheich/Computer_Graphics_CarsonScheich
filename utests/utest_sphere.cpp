#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Shapes/Sphere.h"
#include "ray.h"
#include "vec3.h"
#include "Shader_Light/Light.h"
#include "Scene.h"
#include "Shader_Light/Shader.h"
#include "Shader_Light/Lambertian_Shader.h"

TEST_CASE("RAY HITS SPHERE") {
    Light light(point3(5, 5, 0));


    auto redLambertian =
    std::make_shared<Lambertian>();

    Sphere sphere(point3(0, 0, -5), 1.0, color(1,1,1),redLambertian);
    ray r(
        point3(0, 0, 0),
        vec3(0, 0, -1)
    );
    HitRecord rec;
    REQUIRE(sphere.hit(0.001, 1000.0, r, rec) == true);
}

TEST_CASE("RAY MISSES SPHERE") {
    Light light(point3(5, 5, 0));

    Scene scene;

auto redLambertian =
    std::make_shared<Lambertian>();

    Sphere sphere(point3(0, 0, -5), 1.0,color(1,1,1),redLambertian);
    ray r(
        point3(0, 0, 0),
        vec3(0, 1, 0)
    );
    HitRecord rec;
    REQUIRE(sphere.hit(0.001, 1000.0, r, rec) == false);
}