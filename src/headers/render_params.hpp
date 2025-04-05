#ifndef RENDER_PARAMS_HPP
#define RENDER_PARAMS_HPP
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
class RenderParams {
    public:
        uint16_t screenWidth, screenHeight;
        float fovRadians;
        float nearField, farField;
        glm::mat4 getProjectionMatrix() {
            return glm::perspective(fovRadians, (float)screenWidth / (float)screenHeight, nearField, farField);
        }


};

#endif /* RENDER_PARAMS_HPP */
