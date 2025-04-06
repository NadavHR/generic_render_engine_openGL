#ifndef BASIC_SHADER_HPP
#define BASIC_SHADER_HPP
#include <string>
#include <fstream>
#include <cstring>
#include <gl2.h>
#include <iostream>

class BasicShader {
    public:
        /** creates (and compiles) a basic shader of a certain type
         * @param pathToShader the path to the shader program source code
         * @param shaderType determines which part of the render pipeline this shader will take (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc)
         */
        BasicShader(char * const pathToShader, int shaderType);
        ~BasicShader();

        // links the shader to a program
        void attach(int programID) const; 
    private:
        unsigned int mCompiledID;

};

#endif /* BASIC_SHADER_HPP */
