#include "deferred_point_light.hpp"

DeferredPointLight::DeferredPointLight(glm::vec3 position, glm::vec3 color, float linear, float quadratic, float threshold) :
    position(position), color(color), linearIntensity(linear), quadraticIntensity(quadratic), lightThreshold(threshold) { }

void DeferredPointLight::render(RenderShader &shader)
{
    shader.setVec3(POINT_LIGHT_POSITION_UNIFORM, position);
    shader.setVec3(POINT_LIGHT_COLOR_UNIFORM, color);
    shader.setFloat(POINT_LIGHT_QUADRATIC_UNIFORM, quadraticIntensity);
    shader.setFloat(POINT_LIGHT_LINEAR_UNIFORM, linearIntensity);
    shader.setFloat(POINT_LIGHT_THRESHOLD_UNIFORM, lightThreshold);
    ScreenRenderObject::render(shader);
}
