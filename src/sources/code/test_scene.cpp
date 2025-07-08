#include "test_scene.hpp"

void TestScene::init() {
    // add this target group to the base class's renderer
    renderer.addRenderTargetGroup(mTargetGroup);

    mTestModelRenderObject = std::shared_ptr<DynamicModelRenderObject>(new DynamicModelRenderObject(mTestSphereModel, glm::vec3(0,0,-5), glm::vec3(0), glm::vec3(1)));
    mTestModelRenderObject2 = std::shared_ptr<DynamicModelRenderObject>(new DynamicModelRenderObject(mTestSpaceshipModel, glm::vec3(0.5, 0.5, -2), glm::vec3(0.3, 0, 1), glm::vec3(1)));

    mTargetGroup.addRenderObject(mTestModelRenderObject);
    mTargetGroup.addRenderObject(mTestModelRenderObject2);

    auto testPointLight = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(glm::vec3(-1, 0, -3), glm::vec3(1)));
    auto testPointLight2 = std::shared_ptr<DeferredPointLight>(new DeferredPointLight(glm::vec3(0, -0.5, -3), glm::vec3(1,0,0)));

    auto pointLight1Location = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(mTestSphereModel, glm::vec3(-1, 0, -3), glm::vec3(0.3, 0, 1), glm::vec3(0.1)));
    auto pointLight2Location = std::shared_ptr<ModelRenderObject>(new DynamicModelRenderObject(mTestSphereModel, glm::vec3(0, -0.5, -3), glm::vec3(0.3, 0, 1), glm::vec3(0.1)));

    mTargetGroup.addRenderObject(pointLight1Location);
    mTargetGroup.addRenderObject(pointLight2Location);

    // add the light points to the base class's renderer
    renderer.addPointLight(testPointLight);
    renderer.addPointLight(testPointLight2);
}

void TestScene::periodic() {
    mTestModelRenderObject.get()->rotation += glm::vec3(0.1, 0.05, 0.025);
    mTestModelRenderObject2.get()->rotation += glm::vec3(0, 0, 0.01);
}