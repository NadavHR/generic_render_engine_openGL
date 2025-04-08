#include "render_target_group.hpp"

RenderTargetGroup::RenderTargetGroup(RenderShader &shader, std::function<void(RenderShader&, const RenderParams&)> setRenderSettings,
std::function<void(RenderShader&, const RenderParams&)> postRender) : mShader(shader)
{
    mSetRenderSettings = setRenderSettings;
    mPostRender = postRender;
    mRenderObjects = std::vector<std::shared_ptr<IRenderObject>>();
    mAvailableIndices = std::stack<size_t>();
}

void RenderTargetGroup::drawAll()
{
    for (auto renderObject : mRenderObjects) {
        if (!(renderObject == NULL)) {
            if (renderObject->visible) {
                renderObject->render(mShader);
            }
        }
    }
}

size_t RenderTargetGroup::addRenderObject(std::shared_ptr<IRenderObject> renderObject)
{
    if (mAvailableIndices.empty()){
        size_t index = mRenderObjects.size();
        mRenderObjects.push_back(renderObject);
        return index;
    }
    size_t index = mAvailableIndices.top();
    mAvailableIndices.pop();
    mRenderObjects.assign(index, renderObject);
    return index;
}

std::shared_ptr<IRenderObject> RenderTargetGroup::popRenderObject(size_t index)
{
    auto renderObject = getRenderObject(index);
    mAvailableIndices.push(index);
    mRenderObjects.assign(index, NULL);
    return renderObject;
}

std::shared_ptr<IRenderObject> RenderTargetGroup::getRenderObject(size_t index)
{
    if (index >= mRenderObjects.size()) {
        return NULL;
    }
    return mRenderObjects.at(index);
}

void RenderTargetGroup::render(RenderParams const &params)
{
    mShader.use();
    mSetRenderSettings(mShader, params);
    drawAll();
    mPostRender(mShader, params);
}

RenderShader &RenderTargetGroup::getShader()
{
    return mShader;
}

RenderTargetGroup::~RenderTargetGroup()
{
}