#include "model_render_object.hpp"

ModelRenderObject::ModelRenderObject(Model &model, 
                                    glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale) :
                                     mModel(model), ISpatialRenderObject(position, rotation, scale)
{
    updateTransformation();
}

void ModelRenderObject::updateTransformation()
{
    mModel.setModelTransformation(getTransformationMatrix());
}

void ModelRenderObject::render(RenderShader &shader)
{

    mModel.Draw(shader);
}

ModelRenderObject::~ModelRenderObject() {}

Model &ModelRenderObject::getModel() {
    return mModel;
}

void DynamicModelRenderObject::render(RenderShader &shader)
{
    updateTransformation();
    ModelRenderObject::render(shader);
}
