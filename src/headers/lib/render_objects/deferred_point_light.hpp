#ifndef DEFERRED_POINT_LIGHT_HPP
#define DEFERRED_POINT_LIGHT_HPP
#include "screen_render_object.hpp"
#include <string>


const std::string POINT_LIGHT_POSITION_UNIFORM = "Position"; 
const std::string POINT_LIGHT_COLOR_UNIFORM = "Color";
const std::string POINT_LIGHT_QUADRATIC_UNIFORM = "quadratic";
const std::string POINT_LIGHT_LINEAR_UNIFORM = "linear";
const std::string POINT_LIGHT_THRESHOLD_UNIFORM = "lightThreshold";

class DeferredPointLight : public ScreenRenderObject {
    public:
        DeferredPointLight(glm::vec3 &position, glm::vec3 &color, float &linear, float &quadratic, float &threshold);
        /** renders light source, assumes all relevant uniforms are set correctly (including binding textures), and that the shader is already in use
         * 
         *  also assumes the shader used includes all the correct uniforms (`POINT_LIGHT_POSITION_UNIFORM`, `POINT_LIGHT_COLOR_UNIFORM`, `POINT_LIGHT_LINEAR_UNIFORM`, `POINT_LIGHT_QUADRATIC_UNIFORM`, `POINT_LIGHT_THRESHOLD_UNIFORM`)
         */
        void render(RenderShader &shader) override;

    private:
        // TODO: add getters and setters
         
        // point light position
        glm::vec3 &mPosition;

        // point light color
        glm::vec3 &mColor;

        // point light linear intensity
        float &mLightLinearIntensity;

        // point light quadratic intensity
        float &mLightQuadraticIntensity;

        // point llight threshold
        float &mLightThreshold;
};

#endif /* DEFERRED_POINT_LIGHT_HPP */
