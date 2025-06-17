#ifndef ISPATIAL_RENDER_OBJECT_HPP
#define ISPATIAL_RENDER_OBJECT_HPP
#include <glm/glm.hpp>
#include "irender_object.hpp"
class ISpatialRenderObject : public IRenderObject
{
    public:
        constexpr static const glm::vec4 X_BASE_VECTOR = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        constexpr static const glm::vec4 Y_BASE_VECTOR = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        constexpr static const glm::vec4 Z_BASE_VECTOR = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 getTransformationMatrix() {
            // scale
            glm::mat4 scaleMat(1.0f);  
            scaleMat = glm::scale(scaleMat, scale);         

            // rotation
            glm::mat4 rotationMat(1.0f);  
            rotationMat = glm::rotate(rotationMat, rotation.z, glm::vec3(Z_BASE_VECTOR));
            rotationMat = glm::rotate(rotationMat, rotation.y, glm::vec3(Y_BASE_VECTOR));
            rotationMat = glm::rotate(rotationMat, rotation.x, glm::vec3(X_BASE_VECTOR));

            // translation
            glm::mat4 translationMat(1.0f);
            translationMat = glm::translate(translationMat, position);  

            return translationMat * rotationMat * scaleMat;
        }

    protected:
        ISpatialRenderObject(glm::vec3 initialPosition, glm::vec3 initialRotation, glm::vec3 initialScale) : position(initialPosition), rotation(initialRotation), scale(initialScale) {} 

};



#endif /* ISPATIAL_RENDER_OBJECT_HPP */
