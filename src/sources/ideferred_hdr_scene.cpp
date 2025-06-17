#include "ideferred_hdr_scene.hpp"

void IDeferredHdrScene::renderTo(unsigned int frameBuffer)
{
    // calls periodic to update anything that needs updating before rendering
    periodic();
    // setting view uniforms
    glm::mat4 viewRotation(1.0f);  
    viewRotation = glm::rotate(viewRotation, camRotation.z, glm::vec3(ISpatialRenderObject::Z_BASE_VECTOR));
    viewRotation = glm::rotate(viewRotation, camRotation.y, glm::vec3(ISpatialRenderObject::Y_BASE_VECTOR));
    viewRotation = glm::rotate(viewRotation, camRotation.x, glm::vec3(ISpatialRenderObject::X_BASE_VECTOR));
    DefaultShaders::setViewForShaders(camPosition, viewRotation);
    // setting render params uniforms
    DefaultShaders::setRenderParamsForShaders(renderParams);

    // renders the scene (assuming everything is set correctly in the renderer)
    renderer.render();

    // tone maps and write the result to the given frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    renderer.toneMap();
}

IDeferredHdrScene::IDeferredHdrScene() : renderer(renderParams)
{

}

IDeferredHdrScene::~IDeferredHdrScene()
{
}
