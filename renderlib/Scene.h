#pragma once

#include "renderlib.h"

class Scene {
    public:
    void addObject(std::shared_ptr<Shape> shape) {
        shapes.add(shape);
        bvh.reset();
    }

    void addLight(std::shared_ptr<Light> light){
        lights.push_back(light);
    }

    void buildBVH() {
    if (!shapes.objects.empty()) {
        bvh = std::make_shared<BVHNode>(shapes.objects, 0);
        }
    }

    const shape_list& getObjects() const {
        return shapes;
    }
    
    void addCameras(std::shared_ptr<Camera> cam){
        cameras.push_back(cam);
    }

    const std::shared_ptr<Camera> getCamera(int x){
        return cameras[x];
    } 

    const std::vector<std::shared_ptr<Light>>& getLights() {
        return lights;
    }

    bool isInShadow(const ray& shadowRay, const shape_list& shapes);

    color ray_color(const ray& r,int depth);



    private:
    shape_list shapes;
    std::shared_ptr<BVHNode> bvh;
    std::vector<std::shared_ptr<Light>> lights;
    std::vector<std::shared_ptr<Camera>> cameras;
    

};