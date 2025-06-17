#ifndef IDEFERRED_HDR_SCENE_HPP
#define IDEFERRED_HDR_SCENE_HPP
#include "render_params.hpp"
#include "deferred_renderer.hpp"
#include "default_shaders.hpp"
#include "ispatial_render_object.hpp"

class IDeferredHdrScene
{
public:
    RenderParams renderParams;
    glm::vec3 camPosition = glm::vec3(0);
    glm::vec3 camRotation = glm::vec3(0);
    DeferredRenderer renderer;
    

    // this function gets called once on the first frame
    virtual void init() {}; 
    // this function gets called once every frame right before rendering
    virtual void periodic() {};

    // renders the scene and writes the output to a given frame buffer
    void renderTo(unsigned int frameBuffer);

    IDeferredHdrScene(/* args */);
    ~IDeferredHdrScene();
};


#endif /* IDEFERRED_HDR_SCENE_HPP */
