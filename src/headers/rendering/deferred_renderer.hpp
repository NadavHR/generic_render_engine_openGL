#ifndef DEFERRED_RENDERER_HPP
#define DEFERRED_RENDERER_HPP
#include "frame_buffer_object.hpp"
#include "deferred_point_light.hpp"
#include "ping_pong_buffer_renderer.hpp"
#include "gbuffer.hpp"
#include "default_shaders.hpp"
#include <vector>

class DeferredRenderer : public IRenderer {
    private:
        const PingPongBufferRenderer mPingPongRenderer;
        const GBuffer mBGuffer;
        const unsigned int mOutputFrameTexture, mPingPongTextures[2];
        RenderTargetGroup mPointLightsTargetGroup;

    public:
        DeferredRenderer(RenderParams &renderParams);
        ~DeferredRenderer();

        void render() override;

        void addPointLight(std::shared_ptr<DeferredPointLight> pointLight);
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
