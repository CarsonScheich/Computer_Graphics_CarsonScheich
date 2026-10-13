#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "camera.h"

class Perspective : public Camera {
    public:

    Perspective(
        const point3& orig,
        const vec3& viewDirec,
        double imagePWidth,
        double imagePHeight,
        int imageW,
        int imageH,
        double focal
    ){
        origin = orig;
        viewDirection = viewDirec;
        imagePlaneWidth = imagePWidth;
        imagePlaneHeight = imagePHeight;
        imageWidth = imageW;
        imageHeight = imageH;
        focalLength = focal;
    };

    ray generateRay(double i, double j) override;

    point3 getposition();

    private:
    point3 origin;

    vec3 viewDirection;

    double imagePlaneWidth;
    double imagePlaneHeight;

    int imageWidth;
    int imageHeight;

    double focalLength;
};

#endif
