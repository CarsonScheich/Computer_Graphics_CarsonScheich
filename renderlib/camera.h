#ifndef CAMERA_H
#define CAMERA_H


#include "vec3.h"
#include "ray.h"
//#include "hittable.h"

class Camera{
  public:
    double aspect_ration =1.0;
    int image_width = 200;
    int samples_per_pixel = 10;
    //int max_depth = 10;

    virtual void generateRay(int i, int j,ray &r) = 0;

    virtual ~Camera() = default;

    //void render(const )

    double vfov = 90;

    //void render(const hittable& world){

    //}

  private:
  void initialize() {


        int image_height = int(image_width / aspect_ration);
        image_height = (image_height < 1) ? 1 : image_height;

        int pixel_samples_scale = 1.0 / samples_per_pixel;

        vec3 center = point3(0,0,0);

        auto focal_length = 1.0;
        auto theta = 0; //= degrees_to_radians(vfov);
        auto h= std::tan(theta/2);
        auto viewport_height = 2* h * focal_length;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

       // pixel_delta_u = viewport_u / image_width;
       // pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = 
                center - vec3(0,0, focal_length) - viewport_u/2 - viewport_v/2;
          //  pixel00_loc = viewport_upper_left + .5 * (pixel_delta_u + pixel_delta_v);



  }

};

#endif

         