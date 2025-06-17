#ifndef RENDER_PARAMS_HPP
#define RENDER_PARAMS_HPP
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
class RenderParams {
    public:
        uint16_t screenWidth, screenHeight;
        float fovRadians = 0.7853981633974483f;
        float nearField = 0.1, farField = 1000.0;
        glm::mat4 getProjectionMatrix() const {
            return glm::perspective(fovRadians, (float)screenWidth / (float)screenHeight, nearField, farField);
        }
};

#endif /* RENDER_PARAMS_HPP */
