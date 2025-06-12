#include "default_shaders.hpp"
RenderShader *DefaultShaders::defferedPointLight = NULL;
RenderShader *DefaultShaders::modelRenderDeferredHDR = NULL;
RenderShader *DefaultShaders::toneMapper = NULL;
void DefaultShaders::initializeShaders() {
    BasicShader noChangesVertex(PATH_TO_SHADER("no_changes.vs"), GL_VERTEX_SHADER);
    BasicShader defferedPointLightFragment(PATH_TO_SHADER("deffered_point_light.fs"), GL_FRAGMENT_SHADER);
    defferedPointLight = new RenderShader(noChangesVertex, defferedPointLightFragment);

    BasicShader modelTransformVertex(PATH_TO_SHADER("model_transform.vs"), GL_VERTEX_SHADER);
    BasicShader modelRenderDeferredHDRFragment(PATH_TO_SHADER("model_render_deferred_HDR.fs"), GL_FRAGMENT_SHADER);
    modelRenderDeferredHDR = new RenderShader(modelTransformVertex, modelRenderDeferredHDRFragment);

    BasicShader toneMapperFragment(PATH_TO_SHADER("tone_mapper.fs"), GL_FRAGMENT_SHADER);
    toneMapper = new RenderShader(noChangesVertex, toneMapperFragment);
}