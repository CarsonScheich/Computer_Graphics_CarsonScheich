#pragma once

#include "ray.h"
#include "vec3.h"
#include "Framebuffer.h"

#include "Shapes/Sphere.h"
#include "Shapes/Hittable.h"
#include "Shapes/Triangle.h"

#include "Shader_Light/BlinnPhong.h"
#include "Shader_Light/Lambertian_Shader.h"
#include "Shader_Light/Light.h"
#include "Shader_Light/Mirror.h"
#include "Shader_Light/Point_Light.h"
#include "Shader_Light/Shader.h"

#include "Cameras/camera.h"
#include "Cameras/PerspectiveCamera.h"