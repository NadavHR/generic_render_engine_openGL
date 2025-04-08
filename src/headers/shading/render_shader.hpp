#ifndef RENDER_SHADER_HPP
#define RENDER_SHADER_HPP
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include <iostream>
#include <glad/glad.h> 
#include <glm/gtc/type_ptr.hpp>
#include "basic_shader.hpp"


class RenderShader
{
    private:
        unsigned int mProgramID;
        static unsigned int currentlyUsedProgramID;
        std::unordered_map<std::string, GLint> uniformLookup;

    public:
        RenderShader(BasicShader const vertexShader, BasicShader const fragmentShader);
        ~RenderShader();
        // use/activate the shader
        void use();
        bool isCurrentlyUsed() const;
        // utility uniform functions
        void setBool(const std::string &name, bool value);  
        void setInt(const std::string &name, int value);  
        void setFloat(const std::string &name, float value);
        void setTransform(const std::string &name, glm::mat4 value);
        void setVec3(const std::string &name, glm::vec3 value);
        void setVec2(const std::string &name, glm::vec2 value);
        void setTexture2D(const std::string &name, unsigned int textureUnit, unsigned int textureId);
        GLint getUniformLocation(const std::string &name);
        unsigned int getProgramID() const;
};



#endif /* RENDER_SHADER_HPP */
