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
// #include "headers/shader.hpp"
// #include "headers/renderer.hpp"
// #include "headers/static_utils.hpp"
// #include "headers/camera.hpp"
// #include "headers/model.hpp"
// #include "headers/model_render_object.hpp"
// #include "headers/screen_renderer.hpp"
#include "headers/render_params.hpp"
#include "headers/input.hpp"
#include "headers/timing.hpp"


using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Camera cam(glm::vec3(0.0f, 0.0f, 0.0f));
bool firstMouse = true;
glm::vec2 mousePosition;
float deltaTimeSec = 0;
RenderParams * renderParams;

int main()
{
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(screen::SCR_WIDTH, screen::SCR_HEIGHT, "Space Shooter", NULL, NULL);
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
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_STENCIL_TEST);    
    glEnable(GL_CULL_FACE);  

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

    // transformation
    glm::mat4 projection = renderParams->getProjectionMatrix();
    // render loop
    // -----------

    Shader screenShader("shaders/screen.vs", "shaders/screen.fs");
    screenShader.use();
    screenShader.setInt("screenTexture", 0);
    Renderer renderer = Renderer(screen::SCR_WIDTH, screen::SCR_HEIGHT);
    rendering::renderer = &renderer;
    Crosshair cross = Crosshair(screen::SCR_WIDTH, screen::SCR_HEIGHT, cam);
    crosshair = &cross;
    spaceship = new Spaceship(*crosshair);
    ScreenRenderer screenRenderer(rendering::renderer, &screenShader);
    
    float lastFrameSec = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);  // enable depth test
        renderer.clear(); 
        float currentFrameSec = static_cast<float>(glfwGetTime());
        deltaTimeSec = currentFrameSec - lastFrameSec;
        lastFrameSec = currentFrameSec;
        // cout << 1/timing::deltaTimeSec << endl;
        
        // spaceship->periodic(timing::deltaTimeSec);
        renderer.render();
        TimedEffect::allPeriodic();
        crosshair->periodic();
        screenRenderer.renderToScreen();

        // glBindVertexArray(0); // no need to unbind it every time 
 
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