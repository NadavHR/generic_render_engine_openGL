#include "deferred_renderer.hpp"

#define GEN_HDR_TEXTURE(texture) \
glGenTextures(1, &texture); \
glBindTexture(GL_TEXTURE_2D, texture); \
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, renderParams.screenWidth, renderParams.screenHeight, 0, GL_RGBA, GL_FLOAT, NULL); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

#define CREATE_HDR_TEXTURE() ([&] () { \
    unsigned int texture; \
    GEN_HDR_TEXTURE(texture) \
    return texture; \
})()

DeferredRenderer::DeferredRenderer(RenderParams &renderParams) : 
    IFrameBufferRenderer(renderParams),
    mGBuffer(renderParams), 
    mBrightMapTextureHDR(CREATE_HDR_TEXTURE()),
    mPingPongTexturesHDR{CREATE_HDR_TEXTURE(), CREATE_HDR_TEXTURE()},
    // the original texture will be mPingPongTexturesHDR[1] and we'll write the ambient light there to avoid creating another texture for nothing but also to avoid reading and writing to the same texture at the same time
    mPingPongRenderer(RenderTargetGroup(*DefaultShaders::deferredPointLight), renderParams, mPingPongTexturesHDR[1], mPingPongTexturesHDR)
{
    // attach the textures to this FBO so we can render to it
    bind();
    glBindTexture(GL_TEXTURE_2D, mPingPongTexturesHDR[1]);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mPingPongTexturesHDR[1], 0);
    glBindTexture(GL_TEXTURE_2D, mBrightMapTextureHDR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, mBrightMapTextureHDR, 0);
    unsigned int attachmentsHDR[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachmentsHDR);

    // make sure the frame buffer is complete
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR: Frame buffer incomplete" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

DeferredRenderer::~DeferredRenderer()
{
    mGBuffer.~GBuffer();
    glDeleteTextures(2, mPingPongTexturesHDR);
    glDeleteTextures(1, &mBrightMapTextureHDR);

}

void DeferredRenderer::render() {
    // clear everything
    clear();

    // render the gbuffer
    mGBuffer.render();

    // render ambient light
    bind();
    RenderShader &ambientLightShader = *DefaultShaders::deferredAmbientLight;
    ambientLightShader.use();
    ambientLightShader.setTexture2D(G_ALBEDO_SPEC_UNIFORM, 0, mGBuffer.getAlbedoSpecBuffer());
    ambientLightShader.setTexture2D(G_NORMAL_UNIFORM, 1, mGBuffer.getNormalBuffer());
    ambientLightShader.setTexture2D(G_POSITION_UNIFORM, 2, mGBuffer.getPositionBuffer());
    ambientLightShader.setVec3(AMBIENT_COLOR_UNIFORM, ambientColor);
    ambientLightShader.setFloat(AMBIENT_STRENGTH_UNIFORM, ambientStrength);
    mScreenRenderer.render(ambientLightShader);

    // render point lights
    RenderShader &pointLightShader = *DefaultShaders::deferredPointLight;
    pointLightShader.use();
    pointLightShader.setTexture2D(G_OG_COLORS_UNIFORM, 0, mPingPongTexturesHDR[1]);
    pointLightShader.setTexture2D(G_ALBEDO_SPEC_UNIFORM, 3, mGBuffer.getAlbedoSpecBuffer());
    pointLightShader.setTexture2D(G_NORMAL_UNIFORM, 1, mGBuffer.getNormalBuffer());
    pointLightShader.setTexture2D(G_POSITION_UNIFORM, 2, mGBuffer.getPositionBuffer());
    mPingPongRenderer.render();
}

void DeferredRenderer::clear() const {
    mPingPongRenderer.clear();
    mGBuffer.clear();
}

unsigned int DeferredRenderer::getOutputHDRTexture()
{
    return mPingPongRenderer.getOutputTexture();
}

void DeferredRenderer::addPointLight(std::shared_ptr<DeferredPointLight> pointLight)
{
    mPingPongRenderer.addRenderObject(pointLight);
}

void DeferredRenderer::addRenderTargetGroup(RenderTargetGroup &targetGroup)
{
    mGBuffer.addRenderTargetGroup(&targetGroup);
}

GBuffer& DeferredRenderer::getGbuffer()
{
    return mGBuffer;
}
