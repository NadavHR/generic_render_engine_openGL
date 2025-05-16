#ifndef DEFAULT_SHADERS_HPP
#define DEFAULT_SHADERS_HPP
#include "render_shader.hpp"

#define PATH_TO_SHADER(shader) ("/assets/shaders/" shader)

namespace DefaultShaders {
    RenderShader defferedPointLight;

    void initializeShaders() {
        BasicShader noChangesVertex(PATH_TO_SHADER("no_changes.vs"), GL_VERTEX_SHADER);
        BasicShader defferedPointLightFragment(PATH_TO_SHADER("deffered_point_light.fs"), GL_FRAGMENT_SHADER);
        defferedPointLight = RenderShader(noChangesVertex, defferedPointLightFragment);
    }
}

#endif /* DEFAULT_SHADERS_HPP */
