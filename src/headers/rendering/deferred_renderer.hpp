#ifndef DEFERRED_RENDERER_HPP
#define DEFERRED_RENDERER_HPP
#include "iframe_buffer_object.hpp"
#include "deferred_point_light.hpp"
#include <vector>

class DeferredRenderer : public IFrameBufferRenderer {
    private:
        std::vector<DeferredPointLight *> mLights;
    public:
        DeferredRenderer(RenderParams &renderParams);
        // strength of ambient light
        float ambientStrength;
        // color of ambient light
        glm::vec3 ambientColor;
        // gamma correction value
        float gamma;
        // exposure value
        float exposure;

};

#endif /* DEFERRED_RENDERER_HPP */
