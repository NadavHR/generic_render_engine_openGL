#include "render_target_group.hpp"

RenderTargetGroup::RenderTargetGroup(RenderShader &shader, std::vector<std::shared_ptr<IRenderObject>> renderObjects,
    std::function<void(RenderShader&, const RenderParams&)> preRender,
    std::function<void(RenderShader&, const RenderParams&)> postObjectRender,
    std::function<void(RenderShader&, const RenderParams&)> postRender
) : mShader(shader), mRenderObjects(renderObjects)
{
    mPreRender = preRender;
    mPostRender = postRender;
    mAvailableIndices = std::stack<size_t>();
}

void RenderTargetGroup::setPreRenderFunction(std::function<void(RenderShader &, const RenderParams &)> preRender)
{
    mPreRender = preRender;
}

void RenderTargetGroup::setPostRenderFunction(std::function<void(RenderShader &, const RenderParams &)> postRender)
{
    mPostRender = postRender;
}

void RenderTargetGroup::setPostObjectRenderFunction(std::function<void(RenderShader &, const RenderParams &)> postObjectRender)
{
    mPostObjectRender = postObjectRender;
}

void RenderTargetGroup::drawAll(RenderParams const &params)
{
    for (auto renderObject : mRenderObjects) {
        if (!(renderObject == NULL)) {
            if (renderObject->shouldRender()) {
                renderObject->render(mShader);
                mPostObjectRender(mShader, params);
            }
        }
    }
}

RenderTargetGroup &RenderTargetGroup::operator=(RenderTargetGroup &other)
{
    return other;
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
    mPreRender(mShader, params);
    drawAll(params);
    mPostRender(mShader, params);
}

RenderShader &RenderTargetGroup::getShader()
{
    return mShader;
}

RenderTargetGroup::~RenderTargetGroup()
{
}