#ifndef IFRAME_BUFFER_OBJECT_HPP
#define IFRAME_BUFFER_OBJECT_HPP
#include "render_params.hpp"
#include <glad/glad.h>

// this class represents a basic frame buffer object, you need to provide attachments yourself in child classes
class IFrameBufferObject {
    public:

    // render to the output texture
    virtual void render() {}

    // binds this renderer 
    virtual void bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    }

    // returns the frame buffer object
    unsigned int getFBO() {
        return mFBO;
    }

    // clears the buffers used by this renderer
    virtual void clear() {}

    protected:
        unsigned int mFBO;
        const RenderParams &mRenderParams;
        IFrameBufferObject(const RenderParams &renderParams) : mRenderParams(renderParams) {}

};


#endif /* IFRAME_BUFFER_OBJECT_HPP */
