#include "default_shaders.hpp"
RenderShader *DefaultShaders::defferedPointLight = NULL;

void DefaultShaders::initializeShaders() {
    BasicShader noChangesVertex(PATH_TO_SHADER("no_changes.vs"), GL_VERTEX_SHADER);
    BasicShader defferedPointLightFragment(PATH_TO_SHADER("deffered_point_light.fs"), GL_FRAGMENT_SHADER);
    defferedPointLight = new RenderShader(noChangesVertex, defferedPointLightFragment);
}