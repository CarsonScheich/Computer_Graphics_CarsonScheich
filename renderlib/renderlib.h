#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "ray.h"
#include "vec3.h"
#include "Framebuffer.h"
#include "color.h"
#include "randomOffset.h"

#include "Shapes/Sphere.h"
#include "Shapes/Hittable.h"
#include "Shapes/Hittable_list.h"
#include "Shapes/Triangle.h"
#include "Shapes/Rectangle.h"
#include "Shapes/Box.h"

#include "Shader_Light/BlinnPhong.h"
#include "Shader_Light/Lambertian_Shader.h"
#include "Shader_Light/Light.h"
#include "Shader_Light/Mirror.h"
#include "Shader_Light/Point_Light.h"
#include "Shader_Light/Shader.h"
#include "Shader_Light/Normal.h"

#include "Cameras/camera.h"
#include "Cameras/PerspectiveCamera.h"

#include "Scene.h"