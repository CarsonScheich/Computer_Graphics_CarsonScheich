#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "ray.h"



    TEST_CASE( "THIS TEST THAT RAY ORIGIN AND DIRECTION ARE SET CORRECTLY" )
    {
        vec3 Juliet = {2, 4, 6};
        vec3 Romio = {2, 4, -6};
        
        ray love = ray( Juliet, Romio);
        
        REQUIRE(love.origin().x() == 2);
        REQUIRE(love.origin().y() == 4);
        REQUIRE(love.origin().z() == 6);

        REQUIRE(love.direction().x() == 2);
        REQUIRE(love.direction().y() == 4);
        REQUIRE(love.direction().z() == -6);
    }

    TEST_CASE( "THIS TEST CALCULATIONS POINT ALONG RAY LINE" )
    {
        point3 origin = {2, 4, 6};
        vec3 direction = {1, 2, 3};

        ray r(origin, direction);

        point3 p = r.at(2);

        REQUIRE(p.x() == 4);
        REQUIRE(p.y() == 8);
        REQUIRE(p.z() == 12);
    }

