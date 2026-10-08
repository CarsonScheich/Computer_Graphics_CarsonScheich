#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


#include <vector>
#include <string>
#include "vec3.h"
#include "png++/png.hpp"

class Framebuffer {
    public:

    Framebuffer(int height, int width);

     int getfbWidth ()const;

    int getfbHeight ()const;

    void clear(const vec3& color);

    void setPixel( int i, int j, const vec3& c);

    void exportAsPNG( std::string filename);

    private:
    std::vector< vec3 > fb;
    int width, height;
};


#endif