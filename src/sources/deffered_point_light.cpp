#include "deferred_point_light.hpp"

DeferredPointLight::DeferredPointLight(glm::vec3 &position, glm::vec3 &color, float &linear, float &quadratic, float &threshold) :
    mPosition(position), mColor(color), mLightLinearIntensity(linear), mLightQuadraticIntensity(quadratic), mLightThreshold(threshold) { }

void DeferredPointLight::render(RenderShader &shader)
{
    shader.setVec3(POINT_LIGHT_POSITION_UNIFORM, mPosition);
    shader.setVec3(POINT_LIGHT_COLOR_UNIFORM, mColor);
    shader.setFloat(POINT_LIGHT_QUADRATIC_UNIFORM, mLightQuadraticIntensity);
    shader.setFloat(POINT_LIGHT_LINEAR_UNIFORM, mLightLinearIntensity);
    shader.setFloat(POINT_LIGHT_THRESHOLD_UNIFORM, mLightThreshold);
    ScreenRenderObject::render(shader);
}
