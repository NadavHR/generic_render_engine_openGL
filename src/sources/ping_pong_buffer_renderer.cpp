#include "ping_pong_buffer_renderer.hpp"

PingPongBufferRenderer::PingPongBufferRenderer(RenderTargetGroup targetGroup, const RenderParams &params, const unsigned int originalTexture, const unsigned int textures[2], const std::function<void()> renderFunction1, const std::function<void()> renderFunction2, uint8_t iters)
                                                 : mParams(params), 
                                                mBuffers{PingPongBuffer(params, renderFunction1, textures[0], textures[1]),
                                                        PingPongBuffer(params, renderFunction2, textures[1], textures[0])}, mRenderTargetGroup(targetGroup)
{
    mIterations = iters;
    mOriginalTexture = originalTexture;
    mAction1 = renderFunction1;
    mAction2 = renderFunction2;
    mOutputTexture = originalTexture;
}

unsigned int PingPongBufferRenderer::getOutputTexture()
{
    return mOutputTexture;
}

void PingPongBufferRenderer::setOutputTexture(unsigned int outputTexture)
{
    mOutputTexture = outputTexture;
}

void PingPongBufferRenderer::render()
{
    // this is static in hopes the compiler will realize the lambdas can be optimized as they dont use values that only exist on the stack
    static bool onWhichBuffer = 0;
    onWhichBuffer = 0; // sets it to 0 bc we cant rely on it being 0 on start
    glDisable(GL_DEPTH_TEST); 

    // sets the first buffers render function to first read from the the original texture and then switch to the second buffers texture 
    mBuffers[0].setReadTexture(mOriginalTexture);
    mBuffers[0].setRenderFunction([&] () {
        mAction1();
        mBuffers[0].setReadTexture(mTextures[1]);
        mBuffers[0].setRenderFunction(mAction1);
    });

    // after every object render, run the buffer's render function and than switch buffer 
    mRenderTargetGroup.setPostObjectRenderFunction([&] (RenderShader& shader, const RenderParams& params) {
        mBuffers[onWhichBuffer].render();
        onWhichBuffer = (onWhichBuffer + 1) % 2; // switches buffer
        mBuffers[onWhichBuffer].bind();
    });

    mBuffers[0].bind(); // make sure the correct buffer is bound at the start
    for (uint8_t i = 0; i < mIterations; i++) {
        mRenderTargetGroup.render(mParams);
    }
    glEnable(GL_DEPTH_TEST);
}

void PingPongBufferRenderer::setRenderTargetGroup(RenderTargetGroup renderGroup)
{
    mRenderTargetGroup = renderGroup;
}

void PingPongBuffer::bind()
{
    IFrameBufferObject::bind();
    glBindTexture(GL_TEXTURE_2D, mReadTexture); 
}

void PingPongBuffer::render()
{
    mRenderFunction();
}

void PingPongBuffer::setReadTexture(unsigned int readTexture)
{
    mReadTexture = readTexture;
}

void PingPongBuffer::setRenderFunction(const std::function<void()> renderFunction)
{
    mRenderFunction = renderFunction;
}

PingPongBuffer::PingPongBuffer(const RenderParams &params, const std::function<void()> renderFunction, const unsigned int writeTexture, const unsigned int readTexture) : IFrameBufferRenderer(params)
{
    mRenderFunction = renderFunction;

    mReadTexture = readTexture;

    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    // attach texture to frame buffer
    mWriteTexture = writeTexture;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mWriteTexture, 0);

    // make sure the frame buffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR: Frame buffer incomplete" << std::endl;
    }
}
