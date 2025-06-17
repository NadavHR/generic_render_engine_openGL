#ifndef GBUFFER_HPP
#define GBUFFER_HPP
#include <vector>
#include "render_target_group.hpp"
#include "frame_buffer_object.hpp"
class GBuffer : public IFrameBufferRenderer {
    private:
        std::vector<RenderTargetGroup*> mRenderTargets;  
        unsigned int mgPosition, mgNormal, mgAlbedoSpec; // deferred rendering buffers
        unsigned int mDepthRBO; // the redner buffer object that is used for depth testing
    
    public:
        unsigned int getPositionBuffer() const { return mgPosition; }
        unsigned int getNormalBuffer() const { return mgNormal; }
        unsigned int getAlbedoSpecBuffer() const { return mgAlbedoSpec; }

        // adds a render target group to be rendered by this renderer every frame
        void addRenderTargetGroup(RenderTargetGroup * renderGroup);
        // TODO: add the ability to check and edit the render groups  

        GBuffer(const RenderParams &renderParams);
        ~GBuffer();
        void render() override;
        void clear() const override;
};

#endif /* GBUFFER_HPP */
