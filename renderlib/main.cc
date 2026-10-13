#include "renderlib.h"


#include <iostream>


color ray_color(const ray& r, const shape_list& shape, int depth) {
    if (depth <= 0)
        return color(0, 0, 0);
        
    HitRecord rec;

    if (shape.hit(0.001, 1000.0, r, rec)) {
        ray reflected;

        if (rec.shader->reflectedRay(r, rec, reflected)) {
            return ray_color(reflected, shape, depth - 1);
        }
        return rec.shader->raycolor(rec);

    }
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return color(
        (1.0 - t) * 0.01 + t * 0.35,  // Red
        (1.0 - t) * 0.01 + t * 0.10,  // Green
        (1.0 - t) * 0.08 + t * 0.85   // Blue
);

}



int main(int argc, char* argv[]) {
    // Image

    auto aspect_ratio = 1.0;
    int image_width = 800;
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    Framebuffer fb(image_height , image_width);

    // Camera

Perspective camera(
    point3(0, 0, 0),   // camera position
    vec3(0, 0, -1),    // view direction
    2.0,               // image plane width
    2.0,               // image plane height
    image_width,
    image_height,
    1.5                // focal length
);

Light light(point3(5, 5, 0));

    auto BlinnPhong_ptr =
        std::make_shared<BlinnPhong>(light, camera);

    auto Lambertian_ptr = 
        std::make_shared<Lambertian>(light);

     auto mirror_ptr = 
        std::make_shared<Mirror>();   
 

            auto sphere1 = std::make_shared<Sphere>(point3(0.0,0.0,-10.0),1.0,color(1,.0,.0),Lambertian_ptr);

            auto triangle1 = std::make_shared<Triangle>(point3 (-1.2,-.2,-7),point3(.8,-.5,-5),point3 (.9,0,-5),color(1,0,0),BlinnPhong_ptr);

            auto triangle2 = std::make_shared<Triangle>(point3(0.773205, -0.93923, -7),point3( 0.0330127, 0.94282, -5),point3(-0.45,0.779423,-5),color(0,1,0),Lambertian_ptr);

            auto triangle3 = std::make_shared<Triangle>(point3(0.426795,1.13923,-7),point3(-0.833013,-0.44282,-5),point3(-0.45,-0.779423,-5),color(0,0,1),Lambertian_ptr);


            
            auto spherelam = std::make_shared<Sphere>(point3(2, 0, -7), 1.5,color(1.0,1.0,1.0),mirror_ptr);

            shape_list object;
            
            object.add(triangle1);
            object.add(triangle2);
            object.add(triangle3);
            object.add(sphere1);
            
           object.add(spherelam);

           int rpp_NSquare = 4;
           int max_depth = 15;

           for (int j=0; j<fb.getfbWidth(); ++j){
            for (int i=0; i<fb.getfbHeight(); ++i){
                color c(0.0,0.0,0.0);

                for (int p=0; p<rpp_NSquare; ++p){
                    for (int q=0; q<rpp_NSquare; ++q){

                        float tmin = 1.0;
                        float tmax = std::numeric_limits<float>::infinity();

                        float pOffset = (p + randomOffset())/rpp_NSquare;
                        float qOffset = (q + randomOffset())/rpp_NSquare;

                        ray r = camera.generateRay(i + pOffset, j + qOffset);
                        
                        c += ray_color(r, object,max_depth);
                    }
                }
                c *= (1.0 / (rpp_NSquare * rpp_NSquare));
                fb.setPixel(i,j, color::clamp_color(c));
            }
        }


    std::string output_name = (argc > 1) ? argv[1] : "render";
    fb.exportAsPNG(output_name);
}


/*



int main() {
    // Image
    auto aspect_ratio = 1.0;
    int image_width = 1080;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    Perspective camera(
        point3(0, 0.2, 0),
        vec3(0, 0, -1),
        2.8,
        2.8,
        image_width,
        image_height,
        1.5
    );


    // ==========================================
    // CENTRAL CORE
    // ==========================================

    auto core = std::make_shared<Sphere>(
        point3(0.0, 0.0, -8.0),
        1.15,
        color(0.04, 0.02, 0.08)
    );


    // ==========================================
    // ORBITING SPHERES
    // ==========================================

    auto orb1 = std::make_shared<Sphere>(
        point3(-1.75, 0.85, -7.2),
        0.38,
        color(1.0, 0.08, 0.25)
    );

    auto orb2 = std::make_shared<Sphere>(
        point3(1.65, 0.65, -7.8),
        0.45,
        color(0.05, 0.85, 1.0)
    );

    auto orb3 = std::make_shared<Sphere>(
        point3(-1.45, -1.05, -8.4),
        0.32,
        color(0.65, 0.15, 1.0)
    );

    auto orb4 = std::make_shared<Sphere>(
        point3(1.35, -1.15, -7.0),
        0.28,
        color(1.0, 0.55, 0.05)
    );


    // ==========================================
    // BACKGROUND MOONS
    // ==========================================

    auto moon1 = std::make_shared<Sphere>(
        point3(-3.4, 2.1, -13.0),
        1.25,
        color(0.10, 0.18, 0.55)
    );

    auto moon2 = std::make_shared<Sphere>(
        point3(3.3, 2.0, -15.0),
        1.55,
        color(0.45, 0.05, 0.35)
    );


    // ==========================================
    // CENTER CRYSTAL
    // ==========================================

    auto crystal1 = std::make_shared<Triangle>(
        point3(0.0, 1.55, -6.6),
        point3(-0.75, 0.05, -6.4),
        point3(0.0, -0.25, -6.2),
        color(0.0, 1.0, 0.95)
    );

    auto crystal2 = std::make_shared<Triangle>(
        point3(0.0, 1.55, -6.6),
        point3(0.75, 0.05, -6.4),
        point3(0.0, -0.25, -6.2),
        color(0.15, 0.45, 1.0)
    );

    auto crystal3 = std::make_shared<Triangle>(
        point3(0.0, -1.60, -6.6),
        point3(-0.75, 0.05, -6.4),
        point3(0.0, -0.25, -6.2),
        color(0.75, 0.0, 1.0)
    );

    auto crystal4 = std::make_shared<Triangle>(
        point3(0.0, -1.60, -6.6),
        point3(0.75, 0.05, -6.4),
        point3(0.0, -0.25, -6.2),
        color(1.0, 0.0, 0.65)
    );


    // ==========================================
    // ENERGY WINGS
    // ==========================================

    auto wingLeftTop = std::make_shared<Triangle>(
        point3(-0.55, 0.45, -7.0),
        point3(-2.5, 1.45, -8.6),
        point3(-1.15, 0.10, -7.4),
        color(0.15, 0.35, 1.0)
    );

    auto wingLeftBottom = std::make_shared<Triangle>(
        point3(-0.55, -0.35, -7.0),
        point3(-2.35, -1.55, -8.3),
        point3(-1.05, -0.05, -7.3),
        color(0.55, 0.05, 1.0)
    );

    auto wingRightTop = std::make_shared<Triangle>(
        point3(0.55, 0.45, -7.0),
        point3(2.5, 1.45, -8.6),
        point3(1.15, 0.10, -7.4),
        color(0.0, 0.85, 1.0)
    );

    auto wingRightBottom = std::make_shared<Triangle>(
        point3(0.55, -0.35, -7.0),
        point3(2.35, -1.55, -8.3),
        point3(1.05, -0.05, -7.3),
        color(1.0, 0.10, 0.35)
    );


    // ==========================================
    // WORLD
    // ==========================================

    shape_list object;

    object.add(moon1);
    object.add(moon2);

    object.add(wingLeftTop);
    object.add(wingLeftBottom);
    object.add(wingRightTop);
    object.add(wingRightBottom);

    object.add(core);

    object.add(orb1);
    object.add(orb2);
    object.add(orb3);
    object.add(orb4);

    object.add(crystal1);
    object.add(crystal2);
    object.add(crystal3);
    object.add(crystal4);


    // ==========================================
    // RENDER
    // ==========================================

    std::cout
        << "P3\n"
        << image_width << " "
        << image_height
        << "\n255\n";

    for (int j = 0; j < image_height; j++) {

        std::clog
            << "\rScanlines remaining: "
            << (image_height - j)
            << ' '
            << std::flush;

        for (int i = 0; i < image_width; i++) {

            ray r;

            camera.generateRay(i, j, r);

            color pixel_color =
                ray_color(r, object);

            write_color(
                std::cout,
                pixel_color
            );
        }
    }
}



*/




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
