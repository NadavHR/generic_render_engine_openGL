#ifndef DEFAULT_SHADERS_HPP
#define DEFAULT_SHADERS_HPP
#include "render_shader.hpp"

#define PATH_TO_SHADER(shader) ("/assets/shaders/" shader)

namespace DefaultShaders {
    extern RenderShader *defferedPointLight;

    void initializeShaders();
}

#endif /* DEFAULT_SHADERS_HPP */
