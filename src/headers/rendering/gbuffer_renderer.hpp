#ifndef GBUFFER_RENDERER_HPP
#define GBUFFER_RENDERER_HPP
#include <vector>
#include "render_target_group.hpp"
#include "ibasic_renderer.hpp"
class GBufferRenderer : public IBasicRenderer {
    private:
        std::vector<RenderTargetGroup*> mRenderTargets;  
        unsigned int mgPosition, mgNormal, mgAlbedoSpec; // deferred rendering buffers
    
    public:
        unsigned int getPositionBuffer() { return mgPosition; }
        unsigned int getNormalBuffer() { return mgNormal; }
        unsigned int getAlbedoSpecBuffer() { return mgAlbedoSpec; }

        GBufferRenderer(RenderParams &renderParams);
        void render() override;
        void clear() override;
};

#endif /* GBUFFER_RENDERER_HPP */
