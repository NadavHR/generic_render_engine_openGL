#include "gbuffer.hpp"

void GBuffer::addRenderTargetGroup(RenderTargetGroup *renderGroup)
{
    mRenderTargets.push_back(renderGroup);
}

GBuffer::GBuffer(const RenderParams &renderParams) : IFrameBufferRenderer(renderParams)
{
    #define GEN_TEXTURE(texture, attachment, RGBA_TYPE, data_type) \
    glGenTextures(1, &texture); \
    glBindTexture(GL_TEXTURE_2D, texture); \
    glTexImage2D(GL_TEXTURE_2D, 0, RGBA_TYPE, mRenderParams.frameWidth, mRenderParams.frameHeight, 0, GL_RGBA, data_type, NULL); \
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); \
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); \
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT##attachment, GL_TEXTURE_2D, texture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

    // - normal color buffer
    GEN_TEXTURE(mgNormal, 0, GL_RGBA16F, GL_FLOAT)

    // - position color buffer
    GEN_TEXTURE(mgPosition, 1, GL_RGBA16F, GL_FLOAT)
    
    // - color + specular color buffer
    GEN_TEXTURE(mgAlbedoSpec, 2, GL_RGBA, GL_UNSIGNED_BYTE)
    
    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    unsigned int attachmentsG[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachmentsG);

    // - depth buffer used for depth testing
    glGenRenderbuffers(1, &mDepthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, mRenderParams.frameWidth, mRenderParams.frameHeight);  
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRBO);
    
    // make sure the frame buffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR: Frame buffer incomplete" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GBuffer::~GBuffer()
{
    glDeleteBuffers(1, &mFBO);
    glDeleteRenderbuffers(1, &mDepthRBO);
    glDeleteTextures(1, &mgPosition);
    glDeleteTextures(1, &mgAlbedoSpec);
    glDeleteTextures(1, &mgNormal);
}

void GBuffer::render() 
{
    glEnable(GL_DEPTH_TEST); 
    bind();
    for (RenderTargetGroup * target : mRenderTargets) {
        target->render(mRenderParams);
    }
    glDisable(GL_DEPTH_TEST);
}

void GBuffer::clear() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
