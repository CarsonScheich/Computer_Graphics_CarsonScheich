


add_library(renderlib STATIC
Framebuffer.h 
Framebuffer.cpp
ray.h 
vec3.h 
renderlib.h 
color.h
color.cpp
randomOffset.h
)
target_include_directories(renderlib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(Shapes INTERFACE
Shapes/Hittable.h 
Shapes/Hittable_list.h 
Shapes/Sphere.h 
Shapes/Triangle.h 
)

target_include_directories(Shapes INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(Shader_Light INTERFACE
Shader_Light/BlinnPhong.h 
Shader_Light/Lambertian_Shader.h
Shader_Light/Light.h 
Shader_Light/Mirror.h 
Shader_Light/Point_light.h 
Shader_Light/Shader.h 
)

target_include_directories(Shader_Light INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    )   


add_library(Cameras STATIC 
Cameras/camera.h 
Cameras/PerspectiveCamera.h 
Cameras/PerspectiveCamera.cpp 
)

target_include_directories(Cameras PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    )