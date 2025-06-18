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
    RenderShader &ambientLightShader = *DefaultShaders::deferredAmbientLight;
    RenderShader &pointLightShader = *DefaultShaders::deferredPointLight;
    RenderShader &modelRenderShader = *DefaultShaders::modelRenderDeferredHDR;
    RenderShader &toneMappingShader = *DefaultShaders::toneMapper;
    RenderShader &copyShader = *DefaultShaders::copyBufferShader;
    Model testModel("./assets/models/asteroid/asteroid.gltf");
    DeferredRenderer deferredRenderer(renderParams);
    // transformation

    glm::vec3 testPosition = glm::vec3(0, 0, -5); 
    glm::vec3 testLightPosition = glm::vec3(1, 1, -4);    
    glm::vec3 testRotation = glm::vec3(0, 0, 0);
    glm::vec3 testScale = glm::vec3(1, 1, 1);
    glm::vec3 testColor = glm::vec3(1, 0, 0);
    glm::vec3 testColor2 = glm::vec3(1);
    float testLinear = 0.1f;
    float testQuadratic = 0.01f;
    float testThreshold = 0.8f; 
    DefaultShaders::setRenderParamsForShaders(renderParams);
    DefaultShaders::setViewForShaders(glm::vec3(0), glm::mat4(1));
    auto testModelRenderObject = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(testModel, testPosition, testRotation, testScale));
    auto testModelRenderObject2 = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(testModel, testLightPosition, testRotation, testScale));
    auto testPointLight = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(testLightPosition, testColor, testLinear, testQuadratic, testThreshold));
    auto testPointLight2 = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(testPosition, testColor2, testLinear, testQuadratic, testThreshold));
    RenderTargetGroup testTargetGroup(modelRenderShader);
    std::shared_ptr<ScreenRenderObject> testDrawToScreen = std::shared_ptr<ScreenRenderObject>(new ScreenRenderObject());
    testTargetGroup.addRenderObject(testModelRenderObject2);
    testTargetGroup.addRenderObject(testModelRenderObject);
    testTargetGroup.addRenderObject(testDrawToScreen);
    deferredRenderer.addRenderTargetGroup(testTargetGroup);
    deferredRenderer.addPointLight(testPointLight);
    deferredRenderer.addPointLight(testPointLight2);

    ScreenRenderObject screenRenderer;
    // TestScene testScene = TestScene();
    // glfwSetWindowSize(window, testScene.renderParams.frameWidth, testScene.renderParams.frameHeight);
    // testScene.init();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (true)
    {
        // #define DISPLAY(texture) \
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);\
        // DefaultShaders::copyBufferShader->use(); \
        // DefaultShaders::copyBufferShader->setTexture2D("Buffer", 0, texture);\
        // screenRenderer.render(*DefaultShaders::copyBufferShader); \
        // glfwSwapBuffers(window); \
        // glfwPollEvents();

        // DefaultShaders::setRenderParamsForShaders(renderParams);
        // DefaultShaders::setViewForShaders(glm::vec3(0), glm::mat4(1));
        // deferredRenderer.getGbuffer().render();

        // // deferredRenderer.getGbuffer().render();
        // DISPLAY(deferredRenderer.getGbuffer().getNormalBuffer())
        // DISPLAY(deferredRenderer.getGbuffer().getAlbedoSpecBuffer())
        // DISPLAY(deferredRenderer.getGbuffer().getPositionBuffer())

        // deferredRenderer.getGbuffer().render();

        // DISPLAY(deferredRenderer.getGbuffer().getNormalBuffer())
        // DISPLAY(deferredRenderer.getGbuffer().getAlbedoSpecBuffer())
        // DISPLAY(deferredRenderer.getGbuffer().getPositionBuffer())
        deferredRenderer.render();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        deferredRenderer.toneMap();
        // testScene.renderTo(0);
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