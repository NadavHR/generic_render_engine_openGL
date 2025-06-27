#include "ping_pong_buffer_renderer.hpp"

PingPongBufferRenderer::PingPongBufferRenderer(RenderTargetGroup targetGroup, const RenderParams &params, const unsigned int originalTexture, const unsigned int textures[2], const std::function<void()> renderFunction1, const std::function<void()> renderFunction2, uint8_t iters)
                                                 : mParams(params), 
                                                mTextures{textures[0], textures[1]},
                                                mBuffers{PingPongBuffer(params, renderFunction1, textures[0], textures[1]),
                                                        PingPongBuffer(params, renderFunction2, textures[1], textures[0])}, mRenderTargetGroup(targetGroup)
{
    mIterations = iters;
    mOriginalTexture = originalTexture;
    mAction1 = renderFunction1;
    mAction2 = renderFunction2;
    // after every object render, run the buffer's render function and than switch buffer 
    mRenderTargetGroup.setPostObjectRenderFunction([&] (RenderShader& shader, const RenderParams& params) {
        mBuffers[mOnWhichBuffer].render(); // calls the render function for this buffer before switching to the next

        mOnWhichBuffer = (mOnWhichBuffer + 1) % 2; // switches buffer
        mBuffers[mOnWhichBuffer].bind();
        // set proper active texture unit 
        glActiveTexture(GL_TEXTURE0); 
        // bind the texture
        glBindTexture(GL_TEXTURE_2D, mBuffers[mOnWhichBuffer].mReadTexture);
    });
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int PingPongBufferRenderer::getOutputTexture()
{
    return mBuffers[mOnWhichBuffer].mReadTexture; 
}

void PingPongBufferRenderer::render()
{
    mOnWhichBuffer = 0; // sets it to 0 bc we cant rely on it being 0 on start
    glDisable(GL_DEPTH_TEST); 

    // sets the first buffers render function to first read from the the original texture and then switch to the second buffers texture 
    mBuffers[0].setReadTexture(mOriginalTexture);
    mBuffers[0].setRenderFunction([&] () {
        mAction1();
        mBuffers[0].setReadTexture(mTextures[1]);
        mBuffers[0].setRenderFunction(mAction1);
    });


    mBuffers[0].bind(); // make sure the correct buffer is bound at the start
    for (uint8_t i = 0; i < mIterations; i++) {
        mRenderTargetGroup.render(mParams);
    }
}

void PingPongBufferRenderer::clear() const {
    mBuffers[0].clear();
    mBuffers[1].clear();
}

void PingPongBufferRenderer::setRenderTargetGroup(RenderTargetGroup renderGroup)
{
    mRenderTargetGroup = renderGroup;
}

void PingPongBufferRenderer::addRenderObject(std::shared_ptr<IRenderObject> renderObject)
{
    mRenderTargetGroup.addRenderObject(renderObject);
}

void PingPongBufferRenderer::setIterations(uint8_t iterations)
{
    mIterations = iterations;
}

void PingPongBuffer::bind() const 
{
    FrameBufferObject::bind();
}

void PingPongBuffer::render()
{
    mRenderFunction();
}

void PingPongBuffer::clear() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glClear(GL_COLOR_BUFFER_BIT);
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

    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    // attach texture to frame buffer
    mWriteTexture = writeTexture;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mWriteTexture, 0);

    // make sure the frame buffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR: Frame buffer incomplete" << std::endl;
    }
}
