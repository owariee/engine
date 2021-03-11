#include "Shader.hpp"

#include "Debug.hpp"

Shader::Shader(FileInterface* vertexFile, FileInterface* fragmentFile) {
    uint32_t vertexSize = vertexFile->getSize();
    char* vertexSource = new char[vertexSize];
    vertexFile->read(reinterpret_cast<uint8_t*>(vertexSource), vertexSize);

    uint32_t fragmentSize = fragmentFile->getSize();
    char* fragmentSource = new char[fragmentSize];
    fragmentFile->read(reinterpret_cast<uint8_t*>(fragmentSource), fragmentSize);

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

    delete vertexSource;
    delete fragmentSource;
    
    if (Shader::errorCheck(Shader::program, 0)) 
    {
        Shader::program = 1;
    }
}

Shader::~Shader(void) {
    glDeleteProgram(Shader::program);
}

bool Shader::errorCheck(GLuint bin, int type) {
    int success;
    glGetShaderiv(bin, GL_COMPILE_STATUS, &success);

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

    Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
        error + "_SHADER compilation failed\n" + info);
    return 1;
}

GLuint Shader::compile(const char* shader, int type) {
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
