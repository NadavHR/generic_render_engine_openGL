#ifndef DEFFERED_RENDERER_HPP
#define DEFFERED_RENDERER_HPP
#include "ibasic_renderer.hpp"
class DefferedRenderer : IBasicRenderer {
    public:
        DefferedRenderer(RenderParams &renderParams);
        // strength of ambient light
        float ambientStrength;
        // color of ambient light
        glm::vec3 ambientColor;
        // gamma correction value
        float gamma;
        // exposure value
        float exposure;

};

#endif /* DEFFERED_RENDERER_HPP */
