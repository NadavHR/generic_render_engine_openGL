#ifndef DEFAULT_SHADERS_HPP
#define DEFAULT_SHADERS_HPP
#include "render_shader.hpp"
#include "render_params.hpp"

#define PATH_TO_SHADER(shader) ("./assets/shaders/" shader)

namespace DefaultShaders {
    const std::string VIEW_POSE_UNIFORM = "ViewPos";
    const std::string VIEW_ROT_UNIFORM = "ViewRot";
    const std::string VIEW_TRANSFORM_UNIFORM = "View";
    const std::string TEXEL_SIZE_UNIFORM = "Texel";
    extern RenderShader *deferredPointLight;
    extern RenderShader *deferredAmbientLight;
    extern RenderShader *modelRenderDeferredHDR;
    extern RenderShader *toneMapper;
    void initializeShaders();
    void setViewForShaders(glm::vec3 viewPose, glm::mat4 viewRotation);
    void setRenderParamsForShaders(const RenderParams &renderParms);
}

#endif /* DEFAULT_SHADERS_HPP */
