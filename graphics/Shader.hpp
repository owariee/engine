#ifndef SHADER_HPP
#define SHADER_HPP

#include "FileInterface.hpp"

#include "glad/glad.h"

class Shader {
    public:
        Shader(FileInterface* vertexFile, FileInterface* fragmentFile);
        ~Shader(void);
        void use();
    private:
        GLuint program;
        bool errorCheck(GLuint bin, int type);
        GLuint compile(const char* shader, int type);
};

#endif//SHADER_HPP
