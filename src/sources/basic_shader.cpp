#include "basic_shader.hpp"

char * openRawSource(std::string fileName) {
    std::string outStr;
    std::ifstream read;
    read.open(fileName);
    std::string line;
    while (getline(read, line)){
        outStr += line + '\n';
    }
    read.close();

    char * out = (char *)(malloc(outStr.length() + 1));
    
    strcpy(out, outStr.c_str());

    return out;
}

BasicShader::BasicShader(char *const pathToShader, GLenum shaderType){
    char * shaderSource = openRawSource(pathToShader);

    int success;
    char infoLog[512];
    mCompiledID = glCreateShader(shaderType);
    glShaderSource(mCompiledID, 1, &shaderSource, NULL);
    glCompileShader(mCompiledID);
    // print compile errors if any
    glGetShaderiv(mCompiledID, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(mCompiledID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    free(shaderSource);
}

BasicShader::~BasicShader(){
    glDeleteShader(mCompiledID);
}

void BasicShader::attach(int programID) const {

    glAttachShader(programID, mCompiledID);
}

