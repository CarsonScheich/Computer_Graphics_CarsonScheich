#include "Framebuffer.h"
#include "png++/png.hpp"

Framebuffer::Framebuffer() : width(100), height(100){}


void Framebuffer::clear(const vec3& color = vec3(0,0,0)) 
{
    
    fb.resize(width and height);
    for (int i=0; i < fb.size() ; ++i)
    {
        fb[i] = color;
    }
}

int Framebuffer::getWidth() const { return width;}

int Framebuffer::getHeight() const { return height;}

void Framebuffer::setPixel( int i, int j, const vec3& c) 
{
  fb[j* width + i] = c;
}


void Framebuffer::exportAsPNG( std::string filename)
{
    int w, h;
    png::image< png::rgb_pixel > imData( w, h );
    for (unsigned int idx=0; idx<imData.get_height()*imData.get_width(); ++idx) {
    size_t x = idx % w;
    size_t y = static_cast<size_t>( floor(idx / static_cast<float>(imData.get_width())) );

    float max_distance = sqrt( static_cast<float>((w*w)+ (h*h)) );
    float dist = sqrt( static_cast<float>((x*x)+ (y*y)) ) / max_distance;

    png::byte c[3] = {static_cast<png::byte>(std::clamp( dist * 255.0f, 0.0f, 255.0f )),
                      static_cast<png::byte>(std::clamp( dist * 255.0f, 0.0f, 255.0f )),
                      static_cast<png::byte>(std::clamp( dist * 255.0f, 0.0f, 255.0f )) };


    imData[y][x] =png::rgb_pixel( c[0], c[1], c[2] );
    }
    imData.write(filename + ".png" );
}
