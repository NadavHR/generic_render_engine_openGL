#ifndef PING_PONG_BUFFER_RENDERER_HPP
#define PING_PONG_BUFFER_RENDERER_HPP
#include "frame_buffer_object.hpp"
#include "render_target_group.hpp"
#include <functional>
#include <iostream>
#include <array>

class PingPongBufferRenderer;

class PingPongBuffer : public IFrameBufferRenderer {
    friend PingPongBufferRenderer;
    public:
        void bind() const override;
        void render() override;
        void setReadTexture(unsigned int readTexture);
        void setRenderFunction(const std::function<void()> renderFunction);
        void clear() const;
    private:
        unsigned int mWriteTexture, mReadTexture;
        std::function<void()> mRenderFunction;
        PingPongBuffer(const RenderParams &params, const std::function<void()> renderFunction, const unsigned int writeTexture, const unsigned int readTexture);
};

/** a renderer that renders ping pong buffers
 * IMPORTANT: the texture in the shader will always use the 0 texture unit, that means every other texture must use another unit, you also must first bind the sampler to the correct unit texture, preferabley using using ```RenderShader::setTexture2D``` 
 * assumes the shader only computes one output texture that needs to be ping pong'd */
class PingPongBufferRenderer : public IRenderer
{
    private:
        RenderTargetGroup mRenderTargetGroup;
        const RenderParams &mParams;
        std::function<void()> mAction1, mAction2;
        PingPongBuffer mBuffers[2];
        unsigned int mTextures[2];
        unsigned int mOriginalTexture;
        bool mOnWhichBuffer = 0;
        uint8_t mIterations;

    public:
        /** constructs a ping pong buffer renderer
         * @param targetGroup the target group to be rendered
         * @param params render parameters for the buffers
         * @param originalTexture the texture before the effect is applied 
         * @param textures the textures the ping pong buffers should write to
         * @param renderFunction1 the rendering function of buffer 1 
         * @param renderFunction2 the rendering function of buffer 2 (usually the same as buffer 1)
         * @param iters the ammount of iterations it should run (how many times targetGroup.render() will run)
         */
        PingPongBufferRenderer(RenderTargetGroup targetGroup,
             const RenderParams &params,
             const unsigned int originalTexture,
             const unsigned int textures[2], 
             const std::function<void()> renderFunction1 = [] () {}, 
             const std::function<void()> renderFunction2 = [] () {}, 
             uint8_t iters = 1 );
        /**returns the output texture (use after running `render()`)
         *  
         * this function returns the identifier of the texture last written to by the renderer.
         * each run of `render()` may change which texture will return as it depends on the number of iterations and the size of the render target group
         * it is advised to always render first and than use this function, even though it should return the same texture if you didnt change anything  
         */
        unsigned int getOutputTexture();
        // renders to the output texture (if no output texture was set it defaults to the original texture)
        void render() override;
        // clears both textures
        void clear() const;
        // sets the render target group (copies it)
        void setRenderTargetGroup(RenderTargetGroup renderGroup);
        // adds a render object to be drawn by this renderer
        void addRenderObject(std::shared_ptr<IRenderObject> renderObject);
        // sets how many iterations of the action will run (how many times targetGroup.render() will run)
        void setIterations(uint8_t iterations);
};  

#endif /* PING_PONG_BUFFER_RENDERER_HPP */
