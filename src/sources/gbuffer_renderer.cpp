#include "gbuffer_renderer.hpp"

GBufferRenderer::GBufferRenderer(RenderParams &renderParams) : IBasicRenderer(renderParams)
{
    #define GEN_TEXTURE(texture, attachment, RGBA_TYPE, data_type) \
    glGenTextures(1, &texture); \
    glBindTexture(GL_TEXTURE_2D, texture); \
    glTexImage2D(GL_TEXTURE_2D, 0, RGBA_TYPE, mRenderParams.screenWidth, mRenderParams.screenHeight, 0, GL_RGBA, data_type, NULL); \
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); \
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); \
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT##attachment, GL_TEXTURE_2D, texture, 0);

    glGenFramebuffers(1, &mFBO);
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

    // - depth buffer 
    glGenRenderbuffers(1, &mRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mRenderParams.screenWidth, mRenderParams.screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRBO);

    // make sure the frame buffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR: Frame buffer incomplete" << std::endl;
    }

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBufferRenderer::render()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glBindRenderbuffer(GL_RENDERBUFFER, mRBO);
    // render
    // ------
    glEnable(GL_DEPTH_TEST); 
    for (RenderTargetGroup * target : mRenderTargets) {
        target->render(mRenderParams);
    }
}

void GBufferRenderer::clear()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
