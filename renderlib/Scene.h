#pragma once

#include "renderlib.h"

class Scene {
    public:
    void addObject(std::shared_ptr<Shape> shape) {
        shapes.add(shape);
    }

    void addLight(std::shared_ptr<Light> light){
        lights.push_back(light);
    }

    const shape_list& getObjects() const {
        return shapes;
    }

    const std::vector<std::shared_ptr<Light>>& getLights() {
        return lights;
    }

    bool isInShadow(const ray& shadowRay, const shape_list& shapes);

    color ray_color(const ray& r,int depth);



    private:
    shape_list shapes;
    std::vector<std::shared_ptr<Light>> lights;

};