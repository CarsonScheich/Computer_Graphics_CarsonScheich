#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    return errCount;
}

struct OpenGLCamera {
    glm::vec3 position{0.0f, 0.0f, 10.0f};
    glm::vec3 forward{0.0f, 0.0f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, position + forward, up);
    }

    glm::mat4 getProjectionMatrix(float aspect) const {
        return glm::perspective(
            glm::radians(fov),
            aspect,
            nearPlane,
            farPlane
        );
    }

    glm::vec3 right() const {
        return glm::normalize(glm::cross(forward, up));
    }
};


int main(void)
{
    /* Initialize the library */
    if (!glfwInit()) {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 1.0;
    int winHeight = winWidth / aspectRatio;

    GLFWwindow* window = glfwCreateWindow(
        winWidth,
        winHeight,
        "GLFW Example",
        NULL,
        NULL
    );

    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;

        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::cerr << "GLEW Error! glewInit failed, exiting."
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);

    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
    std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.15, 0.15, 0.15, 1.0);

    int fb_width, fb_height;

    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    //Camera creation
    OpenGLCamera camera;


    GLint major_version;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;


    // Create the triangle VBO
    GLuint m_triangleVBO[1];

    glGenBuffers(1, m_triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    std::vector<float> host_VertexBuffer{
        -3.0f, -3.0f, 0.0f,
         3.0f, -3.0f, 0.0f,
         0.0f,  3.0f, 0.0f
    };

    int numBytes = host_VertexBuffer.size() * sizeof(float);

    glBufferData(
        GL_ARRAY_BUFFER,
        numBytes,
        host_VertexBuffer.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    host_VertexBuffer.clear();


    // Create VAO
    GLuint m_VAO;

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        0
    );

    glBindVertexArray(0);


    double timeDiff = 0.0;
    double startFrameTime = 0.0;
    double endFrameTime = 0.0;
    float triangleRotation = 0.0f;


    // Setup shaders
    sivelab::GLSLObject shader;

    shader.addShader(
        "vertexShader_passthrough.glsl",
        sivelab::GLSLObject::VERTEX_SHADER
    );

    shader.addShader(
        "fragmentShader_passthrough.glsl",
        sivelab::GLSLObject::FRAGMENT_SHADER
    );

    shader.createProgram();


    //Get all three matrix uniforms
    GLuint projMatrixID = shader.createUniform("projMatrix");
    GLuint viewMatrixID = shader.createUniform("viewMatrix");
    GLuint modelMatrixID = shader.createUniform("modelMatrix");


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        endFrameTime = glfwGetTime();
        timeDiff = endFrameTime - startFrameTime;
        startFrameTime = glfwGetTime();
        

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //Get projection and view matrices from camera
        glfwGetFramebufferSize(window, &fb_width, &fb_height);

        if (fb_height == 0) {
            glfwPollEvents();
            continue;
        }

        glViewport(0, 0, fb_width, fb_height);

        float currentAspect =
            static_cast<float>(fb_width) / fb_height;

        glm::mat4 M_proj =
            camera.getProjectionMatrix(currentAspect);

        glm::mat4 M_view =
            camera.getViewMatrix();


        //Create an animated model matrix
        float elapsed = static_cast<float>(glfwGetTime());

        glm::mat4 M_model(1.0f);

        // Move triangle left and right
         M_model = glm::translate(
             M_model,
             glm::vec3(0.0f, 0.0f, 0.0f)
        );
        // Rotate triangle around Y-axis
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            triangleRotation += static_cast<float>(timeDiff);
        }
        M_model = glm::rotate(
            M_model,
            triangleRotation,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        // Scale triangle
        M_model = glm::scale(
            M_model,
            glm::vec3(0.75f)
        );
        //RENDER
        shader.activate();


        //Send all matrices to the GPU
        glUniformMatrix4fv(
            projMatrixID,
            1,
            GL_FALSE,
            glm::value_ptr(M_proj)
        );

        glUniformMatrix4fv(
            viewMatrixID,
            1,
            GL_FALSE,
            glm::value_ptr(M_view)
        );

        glUniformMatrix4fv(
            modelMatrixID,
            1,
            GL_FALSE,
            glm::value_ptr(M_model)
        );


        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        shader.deactivate();


        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for events
        glfwPollEvents();


        // Camera movement
        float moveRatePerFrame = 0.05f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.position += camera.forward * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.position -= camera.right() * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.position -= camera.forward * moveRatePerFrame;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            camera.position += camera.right() * moveRatePerFrame;
        }


        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
            if (timeDiff > 0.0) {
                std::cout << "fps: "
                          << 1.0 / timeDiff
                          << std::endl;
            }
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    glfwTerminate();
    return 0;
}