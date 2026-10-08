#include "png++/png.hpp"
#include "Framebuffer.h"


    Framebuffer::Framebuffer(int height, int width) : width(width), height(height), fb(width * height, vec3(0,0,0)){
         fb.resize( width * height );
        };

     int Framebuffer::getfbWidth() const { return width; }
   

    int Framebuffer::getfbHeight() const { return height; } 

    void Framebuffer::clear(const vec3& color = vec3(0,0,0)) 
    {
        fb.resize(width * height);
        for (int i=0; i < fb.size() ; ++i)
        {
            fb[i] = color;
        }
    }

    void Framebuffer::setPixel( int i, int j, const vec3& c) 
    {
    fb[j* width + i] = c;
    }


  void Framebuffer::exportAsPNG(std::string filename)
{
    png::image<png::rgb_pixel> imData(width, height);

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            // Get the pixel color from the framebuffer
            const vec3& pixel = fb[j * width + i];
            // Clamp RGB values to [0, 1] and convert to [0, 255]
            png::byte r = static_cast<png::byte>(
                std::clamp(pixel.x(), 0.0, 1.0) * 255.999
            );
            png::byte g = static_cast<png::byte>(
                std::clamp(pixel.y(), 0.0, 1.0) * 255.999
            );
            png::byte b = static_cast<png::byte>(
                std::clamp(pixel.z(), 0.0, 1.0) * 255.999
            );
            // Set the PNG pixel
            imData[j][i] = png::rgb_pixel(r, g, b);
        }
    }
    // Export the PNG
    imData.write(filename + ".png");
}
