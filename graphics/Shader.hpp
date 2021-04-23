#ifndef SHADER_HPP
#define SHADER_HPP

#include "FileInterface.hpp"

#include "glad/glad.h"
#include "glm/mat4x4.hpp"

class Shader {
    public:
        Shader(FileInterface* vertexFile, FileInterface* fragmentFile);
        ~Shader(void);
        void use();
        void setUniform(const char* name, glm::mat4 matrix);
        void setUniform(const char* name, glm::vec3 vec3);
    private:
        GLuint program;
        bool errorCheck(GLuint bin, int type);
        GLuint compile(const char* shader, int type);
};

#endif//SHADER_HPP
