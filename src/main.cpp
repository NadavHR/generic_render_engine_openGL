#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <istream>
#include <string>
#include <cstring>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <filesystem>
#include "render_params.hpp"
#include "input.hpp"
#include "timing.hpp"
#include "default_shaders.hpp"
#include "deferred_renderer.hpp"
#include "model_render_object.hpp"
#include "test_scene.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Camera cam(glm::vec3(0.0f, 0.0f, 0.0f));
bool firstMouse = true;
glm::vec2 mousePosition;
float deltaTimeSec = 0;
RenderParams renderParams;

int main()
{
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    renderParams.frameWidth = 900;
    renderParams.frameHeight = 500;
    renderParams.nearField = 0.1f;
    renderParams.farField = 100.0f;
    renderParams.fovRadians = 0.7853981633974483f;

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(renderParams.frameWidth, renderParams.frameHeight, "Render Engine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    } 
    glEnable(GL_CULL_FACE);  
    glDisable(GL_DEPTH_TEST); // by default should be disabled unless needed
    // finished setting up OpenGL API this part is where we run everything that must run first
    // ------------------------------------------------------------------
    DefaultShaders::initializeShaders();

    // here we define everything we need such as scenes
    // ------------------------------------------------------------------ 

    // test ---------------------------------------------------------
    TestScene testScene = TestScene();
    glfwSetWindowSize(window, testScene.renderParams.frameWidth, testScene.renderParams.frameHeight);
    testScene.init();
    while (true)
    {
        testScene.renderTo(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // test ---------------------------------------------------------

    // render loop
    // ---------------------------------------------------------------
    double lastFrameSec = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);  // enable depth test
        // renderer.clear(); 
        double currentFrameSec = glfwGetTime();
        deltaTimeSec = static_cast<float>(currentFrameSec - lastFrameSec);
        lastFrameSec = currentFrameSec;

        cout << 1.0 / deltaTimeSec << endl;
        
        // renderer.render();
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

float getDeltaTimeRawSec() {
    return deltaTimeSec;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    mousePosition.x = xposIn;
    mousePosition.y = yposIn;
    // unsigned int xpos = static_cast<unsigned int>(xposIn);
    // unsigned int ypos = static_cast<unsigned int>(screen::SCR_HEIGHT - 1 - yposIn);

}

glm::vec2 getCursorPosition() {
    return mousePosition;
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}