#include "ping_pong_buffer_renderer.hpp"

PingPongBufferRenderer::PingPongBufferRenderer(RenderTargetGroup targetGroup, const RenderParams &params, const unsigned int originalTexture, const unsigned int textures[2], const std::function<void()> renderFunction1, const std::function<void()> renderFunction2)
                                                 : mParams(params), 
                                                mBuffers{PingPongBuffer(params, renderFunction1, textures[0], textures[1]),
                                                        PingPongBuffer(params, renderFunction2, textures[1], textures[0])}, mRenderTargetGroup(targetGroup)
{
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
    glDisable(GL_DEPTH_TEST); 
    bool onWhich = 0;

    for (uint8_t i = 0; i < mIterations; i++) {
        
    }
    glDisable(GL_DEPTH_TEST);
}

void PingPongBufferRenderer::setIters(uint8_t iters)
{
    mIterations = iters;
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
    bind();
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

PingPongBuffer::PingPongBuffer(const RenderParams &params, const std::function<void()> renderFunction, const unsigned int writeTexture, const unsigned int readTexture) : IFrameBufferObject(params)
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
