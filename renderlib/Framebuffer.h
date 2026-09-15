#include <vector>
#include <string>
#include <vec3.h>

class Framebuffer {
    public:
    Framebuffer() : width(100), height(100) {
        fb.resize( width * height );
    }

    int getWidth() const;

    int getHeight() const;

    void clear(const vec3& color = vec3(0,0,0));


    void setPixel( int i, int j, const vec3& c);

    void exportAsPNG ( std::string filename );

    private:
    std::vector< vec3 > fb;
    int width, height;
};
