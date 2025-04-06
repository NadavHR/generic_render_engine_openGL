#ifndef ISPATIAL_RENDER_OBJECT_HPP
#define ISPATIAL_RENDER_OBJECT_HPP
#include <glm/glm.hpp>
#include "irender_object.hpp"
class ISpatialRenderObject : public IRenderObject
{
    public:
        const glm::vec4 X_BASE_VECTOR = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        const glm::vec4 Y_BASE_VECTOR = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        const glm::vec4 Z_BASE_VECTOR = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        
        glm::mat4 getTransformationMatrix() {
            // scale
            glm::mat4 scale(1.0f);  
            scale = glm::scale(scale, mScale);         

            // rotation
            glm::mat4 rotation(1.0f);  
            rotation = glm::rotate(rotation, mRotation.z, glm::vec3(Z_BASE_VECTOR));
            rotation = glm::rotate(rotation, mRotation.y, glm::vec3(Y_BASE_VECTOR));
            rotation = glm::rotate(rotation, mRotation.x, glm::vec3(X_BASE_VECTOR));

            // translation
            glm::mat4 translation(1.0f);
            glm::vec3 position(mPosition);
            translation = glm::translate(translation, position);  

            return translation * rotation * scale;
        }

    protected:
        glm::vec3 &mPosition;
        glm::vec3 &mRotation;
        glm::vec3 &mScale;

};



#endif /* ISPATIAL_RENDER_OBJECT_HPP */
