#include "deferred_renderer.hpp"

#define GEN_TEXTURE(texture) \
glGenTextures(1, &texture); \
glBindTexture(GL_TEXTURE_2D, texture); \
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, renderParams.screenWidth, renderParams.screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

#define CREATE_TEXTURE() ([&] () { \
    unsigned int texture; \
    GEN_TEXTURE(texture) \
    return texture; \
})()

DeferredRenderer::DeferredRenderer(RenderParams &renderParams) : 
    mBGuffer(renderParams), 
    mPointLightsTargetGroup(*DefaultShaders::defferedPointLight),
    mOutputFrameTexture(CREATE_TEXTURE()),
    mPingPongTextures{CREATE_TEXTURE(), CREATE_TEXTURE()},
    mPingPongRenderer(mPointLightsTargetGroup, renderParams, mOutputFrameTexture, mPingPongTextures)
{

}

DeferredRenderer::~DeferredRenderer()
{
    mBGuffer.~GBuffer();
    glDeleteTextures(2, mPingPongTextures);
    glDeleteTextures(1, &mOutputFrameTexture);

}

void DeferredRenderer::render() {
    
}

void DeferredRenderer::addPointLight(std::shared_ptr<DeferredPointLight> pointLight)
{
    mPointLightsTargetGroup.addRenderObject(pointLight);
}
