#ifndef IFRAME_BUFFER_OBJECT_HPP
#define IFRAME_BUFFER_OBJECT_HPP
#include "render_params.hpp"
#include "irenderer.hpp"
#include <glad/glad.h>

// this class represents a basic frame buffer object, you need to provide attachments yourself in child classes
class IFrameBufferObject {
    public:

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

class IFrameBufferRenderer : public IFrameBufferObject, public IRenderer {
    public:
        // this function is used to write everything to whatever the attachment is (sometimes not much is needed for that but its better to have it than to not)
        virtual void render() override {}
    protected:
        IFrameBufferRenderer(const RenderParams &renderParams) : IFrameBufferObject(renderParams) {}
};


#endif /* IFRAME_BUFFER_OBJECT_HPP */
