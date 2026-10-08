#include <vector>
#include <string>
#include "vec3.h"

class Framebuffer {
    public:
    Framebuffer(int height, int width) : width(width), height(height) {
         fb.resize( width * height );
        };

    int getfbWidth() ;
   

    int getfbHeight() ;

    void clear(const vec3& color);


    void setPixel( int i, int j, const vec3& c);

    void exportAsPNG ( std::string filename );

    private:
    std::vector< vec3 > fb;
    int width, height;
};
