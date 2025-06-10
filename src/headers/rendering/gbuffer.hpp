#ifndef GBUFFER_HPP
#define GBUFFER_HPP
#include <vector>
#include "render_target_group.hpp"
#include "frame_buffer_object.hpp"
class GBuffer : public IFrameBufferRenderer {
    private:
        std::vector<RenderTargetGroup*> mRenderTargets;  
        unsigned int mgPosition, mgNormal, mgAlbedoSpec; // deferred rendering buffers
    
    public:
        unsigned int getPositionBuffer() { return mgPosition; }
        unsigned int getNormalBuffer() { return mgNormal; }
        unsigned int getAlbedoSpecBuffer() { return mgAlbedoSpec; }

        // adds a render target group to be rendered by this renderer every frame
        void addRenderTargetGroup(RenderTargetGroup * renderGroup);
        // TODO: add the ability to check and edit the render groups  

        GBuffer(const RenderParams &renderParams);
        ~GBuffer();
        void render() override;
        void clear() const override;
};

#endif /* GBUFFER_HPP */
