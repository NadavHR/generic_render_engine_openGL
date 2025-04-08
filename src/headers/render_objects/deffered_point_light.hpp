#ifndef DEFFERED_POINT_LIGHT_HPP
#define DEFFERED_POINT_LIGHT_HPP
#include "screen_render_object.hpp"

class DefferedPointLight : public ScreenRenderObject {
    public:
        void render(RenderShader &shader) override;

        // point light position
        glm::vec3 position;

        // point light color
        glm::vec3 color;

        // point light linear intensity
        float lightLinearIntensity;

        // point light quadratic intensity
        float lightQuadraticIntensity;

        // point llight threshold
        float lightThreshold;
};

#endif /* DEFFERED_POINT_LIGHT_HPP */
