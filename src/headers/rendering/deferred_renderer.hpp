#ifndef DEFERRED_RENDERER_HPP
#define DEFERRED_RENDERER_HPP
#include "frame_buffer_object.hpp"
#include "deferred_point_light.hpp"
#include "ping_pong_buffer_renderer.hpp"
#include "gbuffer.hpp"
#include "default_shaders.hpp"
#include <vector>

const std::string G_POSITION_UNIFORM= "gPosition";
const std::string G_NORMAL_UNIFORM= "gNormal";
const std::string G_ALBEDO_SPEC_UNIFORM= "gAlbedoSpec";
const std::string G_OG_COLORS_UNIFORM= "hdrBuffer";
const std::string G_BRIGHT_OUTPUT_UNIFORM= "brightBuffer";


const std::string AMBIENT_COLOR_UNIFORM = "AmbientColor";
const std::string AMBIENT_STRENGTH_UNIFORM = "AmbientStrength";

class DeferredRenderer : public IFrameBufferRenderer {
    private:
        GBuffer mGBuffer;
        const unsigned int mBrightMapTextureHDR, mPingPongTexturesHDR[2];
        PingPongBufferRenderer mPingPongRenderer;
        ScreenRenderObject mScreenRenderer;

    public:
        DeferredRenderer(RenderParams &renderParams);
        ~DeferredRenderer();

        void render() override;

        // clears the screen completely
        void clear() const;

        // returns the HDR texture containing the output, this is not always the same texture
        unsigned int getOutputHDRTexture();

        void addPointLight(std::shared_ptr<DeferredPointLight> pointLight);
        void addRenderTargetGroup(RenderTargetGroup &targetGroup);
        // strength of ambient light
        float ambientStrength = 0.05;
        // color of ambient light
        glm::vec3 ambientColor = glm::vec3(1.0, 1.0, 1.0);
        // gamma correction value
        float gamma;
        // exposure value
        float exposure;
        GBuffer& getGbuffer();

};

#endif /* DEFERRED_RENDERER_HPP */
