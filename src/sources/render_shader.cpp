#include "render_shader.hpp"


unsigned int RenderShader::currentlyUsedProgramID = 0;

GLint RenderShader::getUniformLocation(const std::string &name)
{
    if (auto search = uniformLookup.find(name); search != uniformLookup.end()) {
        return search->second;
    }
    GLint uniform = glGetUniformLocation(mProgramID, name.c_str());
    uniformLookup.insert({name, uniform});
    return uniform;
}

RenderShader::RenderShader(BasicShader const vertexShader, BasicShader const fragmentShader)
{
    int success;
    char infoLog[512];
    mProgramID = glCreateProgram();
    vertexShader.attach(mProgramID);
    fragmentShader.attach(mProgramID);

    glLinkProgram(mProgramID);
    // print linking errors if any
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(mProgramID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

RenderShader::~RenderShader()
{
    glDeleteProgram(mProgramID);
}

void RenderShader::use() 
{ 
    glUseProgram(mProgramID);
    currentlyUsedProgramID = mProgramID;
} 

bool RenderShader::isCurrentlyUsed() const
{
    return (currentlyUsedProgramID == mProgramID);
} 


void RenderShader::setBool(const std::string &name, bool value)
{
    glUniform1i(getUniformLocation(name), (int)value); 
}

void RenderShader::setInt(const std::string &name, int value)
{
    glUniform1i(getUniformLocation(name), value);  
}

void RenderShader::setFloat(const std::string &name, float value)
{
    glUniform1i(getUniformLocation(name), value);  
}

void RenderShader::setTransform(const std::string &name, glm::mat4 value)
{
    glUniformMatrix4fv(
        getUniformLocation(name),
        1, 
        GL_FALSE,
        glm::value_ptr(value));
}

void RenderShader::setVec3(const std::string &name, glm::vec3 value)
{
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void RenderShader::setVec2(const std::string &name, glm::vec2 value)
{
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

unsigned int RenderShader::getProgramID() const
{
    return mProgramID;
}
