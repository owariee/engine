#include "Shader.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>

Shader::Shader(const char* name) {
    std::vector<const char*> code;
    std::vector<int> types;
    std::string extensions[3] = {"vs", "fs", "gs"};

    for (std::string ext : extensions) {
        const char* source = Shader::load_file(name, ext.c_str());
        if (std::strcmp(source, "") == 0) {
            continue;
        }
        code.push_back(source);
        int type = 0;
        if (ext == "vs")
        {
            type = GL_VERTEX_SHADER;
        }
        else if (ext == "fs")
        {
            type = GL_FRAGMENT_SHADER;
        }
        else
        {
            type = GL_GEOMETRY_SHADER;
        }
        types.push_back(type);
    }

    std::vector<GLuint> shaders; 
    for (int i = 0; i < code.size(); i++) {
        GLuint tmp_bin = Shader::compile(code[i], types[i]);
        if (tmp_bin == 1) {
            continue;
        }
        shaders.push_back(tmp_bin);
    }

    GLuint bin = glCreateProgram();

    for (auto shader : shaders) {
        glAttachShader(bin, shader);
    }

    glLinkProgram(bin);

    for (auto shader : shaders) {
        glDeleteShader(shader);
    }
    
    if (Shader::errorCheck(bin, 0)) {
        Shader::program = 1;
    } else {
        Shader::program = bin;
    }

    return;
}

Shader::~Shader(void) {
    glDeleteProgram(Shader::program);
}

bool Shader::errorCheck(GLuint bin, int type) {
    int success = 0;
    glGetShaderiv(bin, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info[512];

        if (type != 0) {
            glGetShaderInfoLog(bin, 512, NULL, info);
        } else  {
            glGetProgramInfoLog(bin, 512, NULL, info);
        }
        
        std::string error = "";
        switch (type) {
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

        std::cout << "ERROR::SHADER::" << error << "::COMPILATION_FAILED\n";
        std::cout << info << std::endl;
        return 1;
    }

    return 0;
}

//  int* Shader::compile(const char* shader, int type)
//  create shader and check for errors
//
//  shader -> shader code pointer
//  type -> shader type
//
//  return pointer to the shader binary if everything okay
//  return 1 if has errors
GLuint Shader::compile(const char* shader, int type) {
    GLuint bin = glCreateShader(type);
    glShaderSource(bin, 1, &shader, NULL);
    glCompileShader(bin);

    if (Shader::errorCheck(bin, type)) {
        return 1;
    } else {
        return bin;
    }
}

const char* Shader::load_file(const char* name, const char* extension) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream stream;

    std::string path = std::string("shader/") + std::string(name) +
                       std::string(".") + std::string(extension);

    try {
        file.open(path);
        stream << file.rdbuf();
        file.close();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_EXIST_OR_CORRUPT" << std::endl;
        return "";
    }

    return stream.str().c_str();
}

void Shader::use() {
    glUseProgram(Shader::program);
}

