#pragma once

#include "ISceneLoader.h"
#include "renderlib.h"

class SceneLoader : public ISceneLoader {
private:
  Scene &m_targetScene; // Reference to the external scene

  std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;

public:
  // The caller provides the scene to be filled
  SceneLoader(Scene &sceneToPopulate)
      : m_targetScene(sceneToPopulate), numShaders(0), numTextures(0) {}

  void reserveCameras(size_t count) override {
    // makes sure the vector has enough space
   // m_targetScene.cameras.reserve(count);
  }
  void reserveLights(size_t count) override {
   // m_targetScene.lights.reserve(count);
  }
  void reserveShapes(size_t count) override {
    //m_targetScene.shapes.reserve(count);
  }
  void reserveShaders(size_t count) override { numShaders = count; }
  void reserveTextures(size_t count) override { numTextures = count; }

  void setSceneParams(const SceneParams &sparams) override {
    std::cout << "Setting scene params." << std::endl;
  }

  void addCamera(const std::string &name, const std::string &type,
                 const ISceneLoader::vec &pos, const ISceneLoader::vec &viewDir,
                 float focalLength, float imagePlaneWidth) override {
    std::cout << "Creating camera: " << name << ", type:" << type << std::endl;
auto cam = std::make_shared<Perspective>(
    point3(pos.x, pos.y, pos.z),
    vec3(viewDir.x, viewDir.y, viewDir.z),
    imagePlaneWidth, imagePlaneWidth, 800, 800, focalLength
);
m_targetScene.addCameras(cam);
  }
  void addPointLight(const ISceneLoader::vec &pos,
                     const ISceneLoader::vec &intensity) override {
    std::cout << "Creating point light." << std::endl;
    auto light = std::make_shared<Light>(point3(pos.x, pos.y, pos.z), color(intensity.x, intensity.y, intensity.z));
    m_targetScene.addLight(light);
  }
  void addAreaLight(const ISceneLoader::vec &pos,
                    const ISceneLoader::vec &color,
                    const ISceneLoader::vec &normal, float width,
                    float length) override {
    std::cout << "Creating area light." << std::endl;
  }
  void addShader(const ISceneLoader::ShaderDesc &shaderDesc) override {
    std::cout << "Creating shader: type=" << shaderDesc.type << std::endl;
    // I place my shaders on an unordered map often
    std::shared_ptr<Shader> Shader;
    if(shaderDesc.type == "Lambertian"){
      Shader = std::make_shared<Lambertian>();
    }
    else if (shaderDesc.type == "BlinnPhongShader"){
      Shader = std::make_shared<BlinnPhong>(*std::dynamic_pointer_cast<Perspective>(m_targetScene.getCamera(0)) ,shaderDesc.phongExp);
    }
    else if (shaderDesc.type == "Mirror"){
      Shader = std::make_shared<Mirror>();
    }
    else if (shaderDesc.type == "NormalShader"){
      Shader = std::make_shared<NormalShader>();
    }
    else {
      std::cout << " Unsupported shader type, skipping." << std::endl;
      return;
    }
    
    m_shaders[shaderDesc.name] = Shader;
  }

  void addShape(const ISceneLoader::ShapeDesc &shapeDesc) override {
    std::cout << "Creating shape: type=" << shapeDesc.type << std::endl;
    auto shape= std::shared_ptr<Shape>();
    if (shapeDesc.type == "triangle"){
      shape = std::make_shared<Triangle>(point3(shapeDesc.v0.x, shapeDesc.v0.y, shapeDesc.v0.z),
      point3(shapeDesc.v1.x, shapeDesc.v1.y, shapeDesc.v1.z),
      point3(shapeDesc.v2.x, shapeDesc.v2.y, shapeDesc.v2.z),
      color(1,0,1) , m_shaders.at(shapeDesc.shaderNameReference));
    }
    else if (shapeDesc.type == "sphere" ){
      shape = std::make_shared<Sphere>(point3(shapeDesc.center.x, shapeDesc.center.y, shapeDesc.center.z)
      , shapeDesc.radius,color(0,1,0), m_shaders.at(shapeDesc.shaderNameReference));
    }
    m_targetScene.addObject(shape);
  }

  void addTexture(const std::string &type, const std::string &name,
                  const std::string &sourceFile) override {
    std::cout << "Creating texture: type=" << type << ", name=" << name
              << ", sourceFile=" << sourceFile << std::endl;
  }

public:
  int numShaders;
  int numTextures;
};
