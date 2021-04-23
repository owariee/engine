#include "Debug.hpp"

#include "glad/glad.h"

#include <cstdio>

#ifdef _DEBUG

void Debug::GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool Debug::GLCheckError(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError()) 
    {
        printf("[OpenGL] (%o) %i:%s %s", error, line, file, func);
        return false;
    }
    return true;
}

#else

void Debug::print(int flag, int index_subsystem, std::string message) 
{
    return;
}

void Debug::GLClearError()
{
    return;
}

bool Debug::GLCheckError(const char* func, const char* file, int line) 
{
    return true;
}

#endif
