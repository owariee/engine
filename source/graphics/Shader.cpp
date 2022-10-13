#include "Shader.hpp"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

Shader::Shader(FileInterface* vertexFile, FileInterface* fragmentFile) {
    uint32_t vertexSize = vertexFile->getSize();
    char* vertexSource = new char[vertexSize+1];
    vertexFile->read(reinterpret_cast<uint8_t*>(vertexSource), vertexSize);
    vertexSource[vertexSize] = '\0';

    uint32_t fragmentSize = fragmentFile->getSize();
    char* fragmentSource = new char[fragmentSize+1];
    fragmentFile->read(reinterpret_cast<uint8_t*>(fragmentSource), fragmentSize);
    fragmentSource[fragmentSize] = '\0';

    GLuint vertexShader = Shader::compile(const_cast<const char*>(vertexSource),
        GL_VERTEX_SHADER);
    GLuint fragmentShader = Shader::compile(const_cast<const char*>(fragmentSource),
        GL_FRAGMENT_SHADER);

    Shader::program = glCreateProgram();

    glAttachShader(Shader::program, vertexShader);
    glAttachShader(Shader::program, fragmentShader);

    glLinkProgram(Shader::program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    delete[] vertexSource;
    delete[] fragmentSource;
    
    if (Shader::errorCheck(Shader::program, 0)) 
    {
        Shader::program = 1;
    }
}

Shader::~Shader(void) {
    glDeleteProgram(Shader::program);
}

bool Shader::errorCheck(unsigned int bin, int type) {
    int success;
    if(type != 0)
    {
        glGetShaderiv(bin, GL_COMPILE_STATUS, &success);
    }  
    else
    {
        glGetProgramiv(bin, GL_LINK_STATUS, &success);
    }

    if(success)
    {
        return 0;
    }

    char info[512];
    if(type != 0)
    {
        glGetShaderInfoLog(bin, 512, NULL, info);
    }  
    else
    {
        glGetProgramInfoLog(bin, 512, NULL, info);
    }

    std::string error = "";
    switch (type) 
    {
        case 0:
            error = "LINK";
            break;
        case GL_VERTEX_SHADER:
            error = "VERTEX";
            break;
        case GL_FRAGMENT_SHADER:
            error = "FRAGMENT";
            break;
        default:
            error = "UNKNOWN";
            break;
    }

    std::cout << "[Graphics] " + error + "_SHADER compilation failed" << std::endl;
    return 1;
}

unsigned int Shader::compile(const char* shader, int type) {
    GLuint bin = glCreateShader(type);
    glShaderSource(bin, 1, &shader, NULL);
    glCompileShader(bin);
    if (Shader::errorCheck(bin, type))
    {
        return 1;
    }
    return bin;
}

void Shader::use() {
    glUseProgram(Shader::program);
}

void Shader::setUniform(const char* name, glm::mat4 matrix)
{
    unsigned int uniformLocation = glGetUniformLocation(Shader::program, name);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniform(const char* name, glm::vec3 vec3)
{
    unsigned int uniformLocation = glGetUniformLocation(Shader::program, name);
    glUniform3fv(uniformLocation, 1, glm::value_ptr(vec3));
}
