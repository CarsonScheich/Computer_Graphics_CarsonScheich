#include "ray.h"
#include "vec3.h"
#include "Sphere.h"
#include "Hittable.h"
#include "Framebuffer.h"


#include <iostream>

/*

vec3 ray_color(const ray& r) {
    return vec3(0,0,0);
}

int main() {

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;


}
    */
    
vec3 ray_color(const ray& r, const Shape& shape) {

    HitRecord rec;

    if (shape.hit(0.001, 1000.0, r, rec)) {

        return 0.5 * (rec.normal + vec3(1,0,0));

    }

        vec3 unit_direction = r.direction() / r.direction().length();

    return 0.5 * vec3(.5,.5,.5);

};

int main() {

    // Image

    auto aspect_ratio = 1.0;
    int image_width = 200;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.5;
    auto viewport_height = 2.0;
    auto viewport_width = 2.0;
    auto camera_center = point3(0, 0, 0);
    auto view_direction = vec3(0,0,-1);

auto forward = view_direction / view_direction.length();

// Pick which direction is "up" in the world
auto world_up = vec3(0, 1, 0);

// Find the camera's right direction
    auto right = cross(forward, world_up);
    right = right / right.length();

// Find the camera's down direction
    auto down = cross(forward, right);

// Build the 2x2 viewport
    auto viewport_u = viewport_width * right;
    auto viewport_v = viewport_height * down;


    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    
    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                         + focal_length * forward
                         - viewport_u/2
                         - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            double rad = 4;
            point3 center = {0.0,0.0,-5.0};

            Sphere sphere(center, rad);

            Shape& shape = sphere;


    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);


            vec3 pixel_color = ray_color(r, shape);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}



/*
#include "ray.h"
#include "vec3.h"

#include <cmath>
#include <iostream>

int main() {

    const int image_width = 3840;
    const int image_height = 2160;

    std::cout << "P3\n"
              << image_width << ' ' << image_height
              << "\n255\n";

    for (int j = 0; j < image_height; ++j) {

        std::clog << "\rScanlines remaining: "
                  << (image_height - j) << ' '
                  << std::flush;

        for (int i = 0; i < image_width; ++i) {

            // Convert pixel coordinates to centered coordinates
            double x =
                (2.0 * i / (image_width - 1.0) - 1.0)
                * (static_cast<double>(image_width) / image_height);

            double y =
                1.0 - 2.0 * j / (image_height - 1.0);

            // Start with a nearly-black space color
            double r = 0.004;
            double g = 0.002;
            double b = 0.020;


            // =========================================================
            // NEBULA BACKGROUND
            // =========================================================

            double nebula =
                0.5 +
                0.5 * std::sin(
                    3.0 * x +
                    2.0 * y +
                    2.5 * std::sin(2.0 * y)
                );

            nebula *=
                0.5 +
                0.5 * std::sin(5.0 * y - 1.5 * x);

            r += 0.025 * nebula;
            g += 0.008 * nebula;
            b += 0.065 * nebula;


            // =========================================================
            // STAR FIELD
            // =========================================================

            double random_value =
                std::sin(i * 127.1 + j * 311.7)
                * 43758.5453;

            double star =
                random_value - std::floor(random_value);

            if (star > 0.9975) {

                double brightness =
                    (star - 0.9975) / 0.0025;

                r += 0.55 * brightness;
                g += 0.70 * brightness;
                b += 1.00 * brightness;
            }


            // =========================================================
            // BLACK HOLE POSITION
            // =========================================================

            double bx = x;
            double by = y + 0.02;

            double distance =
                std::sqrt(bx * bx + by * by);


            // =========================================================
            // OUTER GRAVITATIONAL GLOW
            // =========================================================

            double outer_glow =
                std::exp(
                    -10.0 *
                    std::abs(distance - 0.43)
                );

            r += 0.22 * outer_glow;
            g += 0.04 * outer_glow;
            b += 0.42 * outer_glow;


            // =========================================================
            // PHOTON RING
            // =========================================================

            double photon_ring =
                std::exp(
                    -220.0 *
                    (distance - 0.285) *
                    (distance - 0.285)
                );

            r += 1.00 * photon_ring;
            g += 0.28 * photon_ring;
            b += 0.90 * photon_ring;


            // =========================================================
            // WHITE-HOT INNER RING
            // =========================================================

            double inner_ring =
                std::exp(
                    -900.0 *
                    (distance - 0.255) *
                    (distance - 0.255)
                );

            r += 1.20 * inner_ring;
            g += 0.75 * inner_ring;
            b += 1.10 * inner_ring;


            // =========================================================
            // ACCRETION DISK
            // =========================================================

            // Stretch Y to make the disk look flat
            double disk_y = by * 6.5;

            double disk_radius =
                std::sqrt(
                    bx * bx +
                    disk_y * disk_y
                );

            double disk =
                std::exp(
                    -55.0 *
                    disk_y *
                    disk_y
                );


            if (disk_radius > 0.30 &&
                disk_radius < 1.18) {

                double fade =
                    1.0 -
                    std::abs(disk_radius - 0.68)
                    / 0.50;

                if (fade < 0.0)
                    fade = 0.0;


                // Turbulence in the disk
                double turbulence =
                    0.65 +
                    0.35 *
                    std::sin(
                        38.0 * disk_radius +
                        13.0 *
                        std::sin(7.0 * bx)
                    );

                double energy =
                    disk *
                    fade *
                    turbulence;


                // Change color depending on which side
                double side =
                    0.5 +
                    0.5 *
                    std::tanh(4.0 * bx);


                // Cyan on one side,
                // magenta/orange on the other
                r += energy *
                     (0.15 + 1.25 * side);

                g += energy *
                     (0.85 - 0.35 * side);

                b += energy *
                     (1.45 - 0.35 * side);


                // White-hot center of disk
                double core =
                    std::exp(
                        -420.0 *
                        disk_y *
                        disk_y
                    ) * fade;

                r += 1.00 * core;
                g += 0.72 * core;
                b += 1.15 * core;
            }


            // =========================================================
            // ENERGY JETS
            // =========================================================

            double jet_width =
                std::exp(
                    -95.0 *
                    bx *
                    bx
                );

            double jet_fade =
                std::exp(
                    -1.7 *
                    std::abs(by)
                );

            double jet =
                jet_width *
                jet_fade;


            if (distance > 0.27) {

                r += 0.08 * jet;
                g += 0.35 * jet;
                b += 0.85 * jet;
            }


            // =========================================================
            // EVENT HORIZON
            // =========================================================

            if (distance < 0.235) {

                r = 0.0;
                g = 0.0;
                b = 0.0;
            }


            // =========================================================
            // CINEMATIC VIGNETTE
            // =========================================================

            double edge =
                std::sqrt(
                    (x / 1.5) *
                    (x / 1.5)
                    +
                    (y / 1.05) *
                    (y / 1.05)
                );

            double vignette =
                1.0 -
                0.42 *
                edge *
                edge;

            if (vignette < 0.20)
                vignette = 0.20;


            r *= vignette;
            g *= vignette;
            b *= vignette;


            // =========================================================
            // TONE MAPPING
            // =========================================================

            r = r / (1.0 + r);
            g = g / (1.0 + g);
            b = b / (1.0 + b);


            // Your vec3 represents the RGB pixel
            vec3 pixel_color(r, g, b);

            write_color(
                std::cout,
                pixel_color
            );
        }
    }

    std::clog
        << "\rDone.                 \n";
}

*/
