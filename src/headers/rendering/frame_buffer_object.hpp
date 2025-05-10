#ifndef FRAME_BUFFER_OBJECT_HPP
#define FRAME_BUFFER_OBJECT_HPP
#include "render_params.hpp"
#include "irenderer.hpp"
#include <glad/glad.h>

unsigned int createFrameBuffer() {
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    return fbo;
}

// this class represents a basic frame buffer object, you need to provide attachments yourself in child classes
class FrameBufferObject {
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

    FrameBufferObject(const RenderParams &renderParams) : mRenderParams(renderParams), mFBO(createFrameBuffer()) {}
    ~FrameBufferObject() { glDeleteFramebuffers(1, &mFBO); }

    protected:
        const unsigned int mFBO;
        const RenderParams &mRenderParams;

};

class IFrameBufferRenderer : public FrameBufferObject, public IRenderer {
    public:
        // this function is used to write everything to whatever the attachment is (sometimes not much is needed for that but its better to have it than to not)
        virtual void render() override {}
    protected:
        IFrameBufferRenderer(const RenderParams &renderParams) : FrameBufferObject(renderParams) {}
};


#endif /* FRAME_BUFFER_OBJECT_HPP */
