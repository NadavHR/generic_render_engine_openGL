#ifndef IBASIC_RENDERER_HPP
#define IBASIC_RENDERER_HPP
#include "render_params.hpp"
#include <glad/glad.h>
class IBasicRenderer {
    public:

    // render to the output texture
    virtual void render() {}

    // returns the frame buffer object
    unsigned int getFBO() {
        return mFBO;
    }

    // returns the render buffer object
    unsigned int getRBO() {
        return mRBO;
    }

    // clears the buffers used by this renderer
    virtual void clear() {}

    protected:
        unsigned int mFBO;
        unsigned int mRBO;
        RenderParams &mRenderParams;
        IBasicRenderer(RenderParams &renderParams) : mRenderParams(renderParams) {}

};

#endif /* IBASIC_RENDERER_HPP */
