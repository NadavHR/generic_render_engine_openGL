#include "deferred_renderer.hpp"

PingPongBufferRenderer createPingPongRenderer(RenderParams &renderParams) {
    // TODO: implement
}

DeferredRenderer::DeferredRenderer(RenderParams &renderParams) : mPingPongRenderer(createPingPongRenderer(renderParams)), mBGuffer(renderParams) {

}

void DeferredRenderer::addPointLight(std::shared_ptr<DeferredPointLight> pointLight)
{
    mLights.push_back(pointLight);
    mPingPongRenderer.addRenderObject(pointLight);
}
