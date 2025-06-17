#ifndef MODEL_RENDER_OBJECT_HPP
#define MODEL_RENDER_OBJECT_HPP

#include "ispatial_render_object.hpp"
#include "model.hpp"
class ModelRenderObject : public ISpatialRenderObject {
    public:
        ModelRenderObject(Model &model, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale);
        ~ModelRenderObject() override;
        Model &getModel();

        /**recalculates the models transformation matrix to update where the model will be rendered
         * 
         */
        void updateTransformation();

        /** renders the model (assumes shader already in use)
         * 
         */
        virtual void render(RenderShader &shader) override;


    private:
        Model &mModel;
       
};

class DynamicModelRenderObject : public ModelRenderObject {
    public:
        DynamicModelRenderObject(Model &model, glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale);
        /** renders the model (assumes shader already in use) and also updates the models transformation matrix
         * 
         */
        void render(RenderShader &shader) override;
};

#endif /* MODEL_RENDER_OBJECT_HPP */