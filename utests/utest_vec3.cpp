
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "vec3.h"

//this section is for operation overide is working

//This is the addiston operation works as intended
TEST_CASE( "TEST VEC3 OPOVERRIDE A + B ")
{
    vec3 a = {2,2,2};
    vec3 b = {2,2,2};

    vec3 test_addition = a+b;

    REQUIRE(test_addition.x() == 4);
    REQUIRE(test_addition.y() == 4);
    REQUIRE(test_addition.z() == 4);
}
//This is to test that the multiplication override works as intended
TEST_CASE ( "Test THAT VEC MULTIPLICATION WORKS") {
 
    vec3 a = {4, 6, 8};

    vec3 test_mult = a*2;

    REQUIRE(test_mult.x() == 8);
    REQUIRE(test_mult.y() == 12);
    REQUIRE(test_mult.z() == 16);
}

//This is to make sure the division override works as intended
TEST_CASE( "TEST THAT VEC DEVISION WORKS" ) {
    using Catch::Matchers::WithinAbs;
    vec3 a = {4, 5, 4};
    vec3 b = {4, 5, 9};

    vec3 test_even = a/2;
    vec3 test_odd = b/3;


    REQUIRE_THAT(test_even.x(), WithinAbs(2.0, 0.0000001));
    REQUIRE_THAT(test_even.y(), WithinAbs(2.5, 0.0000001));
    REQUIRE_THAT(test_even.z(), WithinAbs(2.0, 0.0000001));

    REQUIRE_THAT(test_odd.x(), WithinAbs((4.0 / 3.0), 0.0000001));
    REQUIRE_THAT(test_odd.y(), WithinAbs((5.0/ 3.0), 0.0000001));
    REQUIRE_THAT(test_odd.z(), WithinAbs(3, 0.0000001));
}

TEST_CASE ( "TEST THE DOT PRODUCT" ) {
    using Catch::Matchers::WithinAbs;
    vec3 a = {2, 0, 8};
    vec3 b = {8, 4, -2};

    double dot_product = dot( a, b );

    REQUIRE_THAT(dot_product, WithinAbs(0, 0.00000001));
}

TEST_CASE ( "TEST THE CROSS PRODUCT" ) {
    
    vec3 a = {1, 2, 3};
    vec3 b = {4, 5, 6};

    vec3 test_cross = cross( a, b );

    REQUIRE(test_cross.x() == -3);
    REQUIRE(test_cross.y() == 6);
    REQUIRE(test_cross.z() == -3);
}