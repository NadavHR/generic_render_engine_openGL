#include "default_shaders.hpp"
RenderShader *DefaultShaders::deferredPointLight = NULL;
RenderShader *DefaultShaders::deferredAmbientLight = NULL;
RenderShader *DefaultShaders::modelRenderDeferredHDR = NULL;
RenderShader *DefaultShaders::toneMapper = NULL;
RenderShader *DefaultShaders::copyBufferShader = NULL;

void DefaultShaders::initializeShaders() {
    BasicShader noChangesVertex(PATH_TO_SHADER("no_changes.vs"), GL_VERTEX_SHADER);
    BasicShader defferedPointLightFragment(PATH_TO_SHADER("deffered_point_light.fs"), GL_FRAGMENT_SHADER);
    // only initialize if not already initialized
    if (!deferredPointLight) {
        deferredPointLight = new RenderShader(noChangesVertex, defferedPointLightFragment);
    }

    BasicShader defferedAmbientLightFragment = BasicShader(PATH_TO_SHADER("ambient_light_deferred.fs"), GL_FRAGMENT_SHADER);
    if (!deferredAmbientLight) {
        deferredAmbientLight = new RenderShader(noChangesVertex, defferedAmbientLightFragment);
    }

    BasicShader toneMapperFragment(PATH_TO_SHADER("tone_mapper.fs"), GL_FRAGMENT_SHADER);
    if (!toneMapper) {
        toneMapper = new RenderShader(noChangesVertex, toneMapperFragment);
    }

    BasicShader copyFragment(PATH_TO_SHADER("copy.fs"), GL_FRAGMENT_SHADER);
    if (!copyBufferShader) {
        copyBufferShader = new RenderShader(noChangesVertex, copyFragment);
    }

    BasicShader modelTransformVertex(PATH_TO_SHADER("model_transform.vs"), GL_VERTEX_SHADER);
    BasicShader modelRenderDeferredHDRFragment(PATH_TO_SHADER("model_render_deferred_HDR.fs"), GL_FRAGMENT_SHADER);
    if (!modelRenderDeferredHDR) {
        modelRenderDeferredHDR = new RenderShader(modelTransformVertex, modelRenderDeferredHDRFragment);
    }
}

void DefaultShaders::setViewForShaders(glm::vec3 const viewPose, glm::mat4 const viewRotation)
{
    deferredAmbientLight->use();
    deferredAmbientLight->setVec3(VIEW_POSE_UNIFORM, viewPose);
    deferredAmbientLight->setTransform(VIEW_ROT_UNIFORM, viewRotation);

    deferredPointLight->use();
    deferredPointLight->setVec3(VIEW_POSE_UNIFORM, viewPose);

    modelRenderDeferredHDR->use();
    modelRenderDeferredHDR->setTransform(VIEW_TRANSFORM_UNIFORM, glm::translate(viewRotation, viewPose));
}

void DefaultShaders::setRenderParamsForShaders(const RenderParams &renderParms)
{
    deferredAmbientLight->use();
    deferredAmbientLight->setVec2(TEXEL_SIZE_UNIFORM, glm::vec2(1.0 / renderParms.frameWidth, 1.0 / renderParms.frameHeight));

    modelRenderDeferredHDR->use();
    modelRenderDeferredHDR->setTransform(PROJECTION_MATRIX_UNIFORM, renderParms.getProjectionMatrix());
}
