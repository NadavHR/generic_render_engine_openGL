#ifndef TEST_SCENE_HPP
#define TEST_SCENE_HPP
#include "ideferred_hdr_scene.hpp"
#include "model.hpp"
#include "model_render_object.hpp"

class TestScene : public IDeferredHdrScene {
    private:
        Model mTestSphereModel = Model("./assets/models/sphere/sphere.gltf");
        Model mTestSpaceshipModel = Model("./assets/models/spaceship/basic_spaceship.gltf");
        std::shared_ptr<DynamicModelRenderObject> mTestModelRenderObject;
        std::shared_ptr<DynamicModelRenderObject> mTestModelRenderObject2;
        RenderTargetGroup mTargetGroup = RenderTargetGroup(*DefaultShaders::modelRenderDeferredHDR);
    public:
        void init() override;

        void periodic() override;
};

#endif /* TEST_SCENE_HPP */
