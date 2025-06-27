#include "test_scene.hpp"

void TestScene::init() {
    // add this target group to the base class's renderer
    renderer.addRenderTargetGroup(mTargetGroup);

    auto testModelRenderObject = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(mTestAsteroidModel, glm::vec3(0,0,-5), glm::vec3(0), glm::vec3(1)));
    auto testModelRenderObject2 = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(mTestSpaceshipModel, glm::vec3(0.5, 0.5, -2), glm::vec3(0.3, 0, 1), glm::vec3(1)));

    mTargetGroup.addRenderObject(testModelRenderObject);
    mTargetGroup.addRenderObject(testModelRenderObject2);

    auto testPointLight = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(glm::vec3(-1, 0, -5), glm::vec3(1)));
    auto testPointLight2 = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(glm::vec3(0, -1, -4), glm::vec3(1,0,0)));

    // add the light points to the base class's renderer
    renderer.addPointLight(testPointLight);
    renderer.addPointLight(testPointLight2);
}

void TestScene::periodic() {

}