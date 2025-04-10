#ifndef PING_PONG_BUFFER_RENDERER_HPP
#define PING_PONG_BUFFER_RENDERER_HPP
#include "iframe_buffer_object.hpp"
#include "render_target_group.hpp"
#include <functional>
#include <iostream>
#include <array>
// a renderer that renders ping pong buffers, assumes the shader only computes one output texture that needs to be ping pong'd 
class PingPongBufferRenderer
{
    private:
        RenderTargetGroup mRenderTargetGroup;
        const RenderParams &mParams;
        std::function<void()> mAction1, mAction2;
        PingPongBuffer mBuffers[2];
        unsigned int mTextures[2];
        unsigned int mOriginalTexture;
        unsigned int mOutputTexture;
        uint8_t mIterations;
    public:
        /** constructs a ping pong buffer renderer
         * @param targetGroup the target group to be rendered
         * @param params render parameters for the buffers
         * @param originalTexture the texture before the effect is applied (and the default output texture)
         * @param textures the textures the ping pong buffers should write to
         * @param renderFunction1 the rendering function of buffer 1 
         * @param renderFunction2 the rendering function of buffer 2 (usually the same as buffer 1)
         */
        PingPongBufferRenderer(RenderTargetGroup targetGroup, const RenderParams &params, const unsigned int originalTexture, const unsigned int textures[2], const std::function<void()> renderFunction1, const std::function<void()> renderFunction2 );
        // returns the output texture (if no output texture was set it defaults to the original texture)
        unsigned int getOutputTexture();
        // sets the output texture (if no output texture was set it defaults to the original texture)
        void setOutputTexture(unsigned int outputTexture);
        // renders to the output texture (if no output texture was set it defaults to the original texture)
        void render();
        // sets how many iterations should be performed 
        void setIters(uint8_t iters);
        // sets the render target group (copies it)
        void setRenderTargetGroup(RenderTargetGroup renderGroup);

};

class PingPongBuffer : IFrameBufferObject {
    friend PingPongBufferRenderer;
    public:
        void bind() override;
        void render() override;
        void setReadTexture(unsigned int readTexture);
        void setRenderFunction(const std::function<void()> renderFunction);
    private:
        unsigned int mWriteTexture, mReadTexture;
        std::function<void()> mRenderFunction;
        PingPongBuffer(const RenderParams &params, const std::function<void()> renderFunction, const unsigned int writeTexture, const unsigned int readTexture);
};

#endif /* PING_PONG_BUFFER_RENDERER_HPP */
