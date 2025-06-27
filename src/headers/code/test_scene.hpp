#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP
#include "ideferred_hdr_scene.hpp"
#include "model.hpp"
#include "model_render_object.hpp"

class TestScene : public IDeferredHdrScene {
    private:
        Model mTestAsteroidModel = Model("./assets/models/asteroid/asteroid.gltf");
        Model mTestSpaceshipModel = Model("./assets/models/spaceship/basic_spaceship.gltf");
        RenderTargetGroup mTargetGroup = RenderTargetGroup(*DefaultShaders::modelRenderDeferredHDR);
    public:
        void init() override;

        void periodic() override;
};

#endif /* TEST_SCENE_HPP */
