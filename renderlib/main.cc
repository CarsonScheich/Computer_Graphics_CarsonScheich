#include "renderlib.h"

int main(int argc, char* argv[]) {
    // Image

    auto aspect_ratio = 1.0;
    int image_width = 500;
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    Framebuffer fb(image_height , image_width);

    // Camera

Perspective camera(
    point3(0, 3, 3),   // camera position
    vec3(0, -0.4, -1),    // view direction
    .5,               // image plane width
    .5,               // image plane height
    image_width,
    image_height,
    .4                // focal length
);

Scene scene;

auto light1 = std::make_shared<Light>(point3(-5,8,5),color(.7,.6,.45));
scene.addLight(light1);

auto light2 = std::make_shared<Light>(point3(6,6,2),color(.35,.45,.7));
scene.addLight(light2);

    auto BlinnPhong_ptr64 =
        std::make_shared<BlinnPhong>(camera, 64);

    auto BlinnPhong_ptr16 =
        std::make_shared<BlinnPhong>(camera, 16);  

    auto BlinnPhong_ptr32 =
        std::make_shared<BlinnPhong>(camera, 32); 

    auto Lambertian_ptr = 
        std::make_shared<Lambertian>();

     auto mirror_ptr = 
        std::make_shared<Mirror>();  

    auto normal_ptr = 
    std::make_shared<NormalShader>();
 
// ==========================================
// SCENE SETUP
// ==========================================

auto floor1 = std::make_shared<Triangle>(
    point3(-50, 0, 50),
    point3(50, 0 , 50),
    point3(50, 0, -50),
    color(.6, .6, .6),
    Lambertian_ptr
);

auto floor2 = std::make_shared<Triangle>(
    point3(-50, 0, 50),
    point3(50, 0 , -50),
    point3(-50, 0, -50),
    color(.6, .6, .6),
    Lambertian_ptr
);

auto wall1 = std::make_shared<Triangle>(
    point3(-4, 0, -6),
    point3(4, 0, -6),
    point3(4, 4, -6),
    color(1, 1, 1),
    mirror_ptr
);

auto wall2 = std::make_shared<Triangle>(
    point3(-4, 0, -6),
    point3(4, 4, -6),
    point3(-4, 4, -6),
    color(1, 1, 1),
    mirror_ptr
);

auto floatingtri = std::make_shared<Triangle>(
    point3(0.9, 1.4, -0.6),
    point3(1.9, 1.4, -0.6),
    point3(1.4, 2.2, -1.1),
    color(.9, .8, .1),
    Lambertian_ptr
);

auto GreenSphere = std::make_shared<Sphere>(
    point3(-2, 0.8, -3),
    .8,
    color(.2, .8, .2),
    Lambertian_ptr
);

auto RedSphere =std::make_shared<Sphere>(
    point3(-1.1, 0.6, -1.2),
    .6,
    color(.8, .1, .1),
    BlinnPhong_ptr64
);

auto normal = std::make_shared<Sphere>(
    point3(0, 0.9, -3.5),
    .9,
    color(0,0,0),
    normal_ptr
);

auto BlueSphere = std::make_shared<Sphere>(
    point3(0.3, 0.45, -1.6),
    .45,
    color(.1, .2, .8),
    BlinnPhong_ptr16
);


auto mirrorSphere = std::make_shared<Sphere>(
    point3(2, 1, -3),
    1,
    color(1,1,1),
    mirror_ptr
);

auto FrontMirrorPShere = std::make_shared<Sphere>(
    point3(1.5, 0.5, 0.3),
    .5,
    color(1,1,1),
    mirror_ptr
);

auto diffuse = std::make_shared<Sphere>(
    point3(-1.3, 0.45, 0.4),
    .45,
    color(.2, .7, .7),
    Lambertian_ptr
);

//BEHIND CAMERA

auto orangeSphere = std::make_shared<Sphere>(
    point3(0.3, 1, 5),
    1,    
    color(.95, .5, .1),
    BlinnPhong_ptr32
);

auto PurpleSphere = std::make_shared<Sphere>(
    point3(2.4, 0.8, 4.8),
    .8,
    color(.6, .2, .8),
    Lambertian_ptr
);

auto box = std::make_shared<Box>(
    point3(-3.5, 0.0, -4.0),  // Minimum corner
    point3(-1.5, 1.0, -3.0),  // Maximum corner
    color(.2, .5, .9),
    Lambertian_ptr

);

/*
// CENTER MIRROR SPHERE
auto mirrorBall = std::make_shared<Sphere>(
    point3(0.0, -0.35, -7.5),
    1.15,
    color(1.0, 1.0, 1.0),
    mirror_ptr
);

// LEFT RED SPHERE
auto redBall = std::make_shared<Sphere>(
    point3(-3.0, -0.55, -8.0),
    0.95,
    color(1.0, 0.14, 0.22),
    Lambertian_ptr
);

// RIGHT BLUE SPHERE
auto blueBall = std::make_shared<Sphere>(
    point3(2.75, -0.55, -8.0),
    0.95,
    color(0.08, 0.55, 1.0),
    Lambertian_ptr
);

// BACK GOLD SPHERE
auto goldBall = std::make_shared<Sphere>(
    point3(-1.9, -0.75, -11.5),
    0.75,
    color(1.0, 0.72, 0.16),
    Lambertian_ptr
);


// ==========================================
// GRAY FLOOR (TWO TRIANGLES)
// ==========================================

auto floorA = std::make_shared<Triangle>(
    point3(-30.0, -1.5, -3.0),
    point3(30.0, -1.5, -3.0),
    point3(-30.0, -1.5, -40.0),
    color(0.45, 0.45, 0.45),
    Lambertian_ptr
);

auto floorB = std::make_shared<Triangle>(
    point3(30.0, -1.5, -3.0),
    point3(30.0, -1.5, -40.0),
    point3(-30.0, -1.5, -40.0),
    color(0.45, 0.45, 0.45),
    Lambertian_ptr
);

// ==========================================
// ADD OBJECTS TO SCENE
// ==========================================

scene.addObject(floorA);
scene.addObject(floorB);

scene.addObject(redBall);
scene.addObject(blueBall);
scene.addObject(goldBall);
scene.addObject(mirrorBall);

*/


scene.addObject(floor1);
scene.addObject(floor2);
scene.addObject(wall1);
scene.addObject(wall2);
scene.addObject(floatingtri);
scene.addObject(GreenSphere);
scene.addObject(RedSphere);
scene.addObject(normal);
scene.addObject(BlueSphere);
scene.addObject(mirrorSphere);
scene.addObject(FrontMirrorPShere);
scene.addObject(diffuse);
scene.addObject(orangeSphere);
scene.addObject(PurpleSphere);
scene.addObject(box);



           int rpp_NSquare = 10;
           int max_depth = 5;

           #pragma omp parallel for
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
                        
                        c += scene.ray_color(r, max_depth);
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





            auto sphere1 = std::make_shared<Sphere>(point3(0.0,0.0,-10.0),1.0,color(1,.0,.0),Lambertian_ptr);

            auto triangle1 = std::make_shared<Triangle>(point3 (-1.2,-.2,-7),point3(.8,-.5,-5),point3 (.9,0,-5),color(1,0,0),BlinnPhong_ptr);

            auto triangle2 = std::make_shared<Triangle>(point3(0.773205, -0.93923, -7),point3( 0.0330127, 0.94282, -5),point3(-0.45,0.779423,-5),color(0,1,0),Lambertian_ptr);

            auto triangle3 = std::make_shared<Triangle>(point3(0.426795,1.13923,-7),point3(-0.833013,-0.44282,-5),point3(-0.45,-0.779423,-5),color(0,0,1),Lambertian_ptr);


            
            auto spherelam = std::make_shared<Sphere>(point3(2, 0, -7), 1.5,color(1.0,1.0,1.0),mirror_ptr);

            shape_list object;
            
            scene.addObject(triangle1);
            scene.addObject(triangle2);
            scene.addObject(triangle3);
            scene.addObject(sphere1);
            
           scene.addObject(spherelam);







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
