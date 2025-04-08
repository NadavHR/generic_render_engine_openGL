#ifndef IBASIC_RENDERER_HPP
#define IBASIC_RENDERER_HPP
#include "render_params.hpp"
class IBasicRenderer {
    public:

    // render to the output texture
    virtual void render() {}

    // returns the texture this render renders to
    unsigned int getTexture() {
        return mTexture;
    }

    // clears the buffers used by this renderer
    virtual void clear() {}

    protected:
        unsigned int mTexture;
        unsigned int mFBO;
        unsigned int mRBO;
        RenderParams &mRenderParams;

};

#endif /* IBASIC_RENDERER_HPP */
