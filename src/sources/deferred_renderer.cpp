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
    mGBuffer(renderParams), 
    mBrightMapTextureHDR(CREATE_HDR_TEXTURE()),
    mPingPongTexturesHDR{CREATE_HDR_TEXTURE(), CREATE_HDR_TEXTURE()},
    mPingPongRenderer(RenderTargetGroup(*DefaultShaders::defferedPointLight), renderParams, mPingPongTexturesHDR[0], mPingPongTexturesHDR)
{

}

DeferredRenderer::~DeferredRenderer()
{
    mGBuffer.~GBuffer();
    glDeleteTextures(2, mPingPongTexturesHDR);
    glDeleteTextures(1, &mBrightMapTextureHDR);

}

void DeferredRenderer::render() {
    mGBuffer.render();
    RenderShader &shader = *DefaultShaders::defferedPointLight;
    shader.setTexture2D(G_ALBEDO_SPEC_UNIFORM, 0, mGBuffer.getAlbedoSpecBuffer());
    shader.setTexture2D(G_NORMAL_UNIFORM, 1, mGBuffer.getNormalBuffer());
    shader.setTexture2D(G_POSITION_UNIFORM, 2, mGBuffer.getPositionBuffer());
    mPingPongRenderer.render();
}

void DeferredRenderer::clear() const {
    mPingPongRenderer.clear();
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
