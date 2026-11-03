#include "PerspectiveCamera.h"


ray Perspective::generateRay(double i, double j) {
        vec3 forward = viewDirection / viewDirection.length();

        vec3 world_up(0, 1, 0);

        vec3 right = cross(forward, world_up);
        right = right / right.length();

        vec3 down = cross(forward, right);

        vec3 viewport_u = imagePlaneWidth * right;
        vec3 viewport_v = imagePlaneHeight * down;

        vec3 pixel_delta_u = viewport_u / imageWidth;
        vec3 pixel_delta_v = viewport_v / imageHeight;

        point3 viewport_upper_left =
         origin
         + focalLength * forward
         - viewport_u / 2
         - viewport_v / 2;

        point3 pixel00_loc =
         viewport_upper_left
         + 0.5 * (pixel_delta_u + pixel_delta_v);

        point3 pixel_center =
         pixel00_loc
         + (i * pixel_delta_u)
         + (j * pixel_delta_v);

        vec3 ray_direction = pixel_center - origin;
        

        ray r = ray(origin, ray_direction);
        return r;
    }

    point3 Perspective::getposition() {
        return origin;
    }

    




