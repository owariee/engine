#include "Debug.hpp"

#include "fmt/core.h"
#include "fmt/color.h"
#include "glad/glad.h"

#include <iostream>

#ifdef _DEBUG

void Debug::print(int flag, int index_subsystem, std::string message) 
{
    fmt::terminal_color color = fmt::terminal_color::bright_magenta;
    std::string type = "";
    const char* subsystem[] = { "Debug","Memory","Graphics","VFS","Sound","Window","GUI","Lua" };
    switch (flag)
    {
    case Error:
        color = fmt::terminal_color::bright_red;
        type = "ERROR";        
        break;
    case Warning:
        color = fmt::terminal_color::yellow;
        type = "WARNING";
        break;
    case Info:
        color = fmt::terminal_color::cyan;
        type = "INFORMATION";
        break;
    case Trace:
        color = fmt::terminal_color::bright_green;
        type = "TRACE";
        break;
    default:
        type = "UKNOWN";
        break;
    }
    fmt::print(fg(color), "{}::{}: {}.\n",type, subsystem[index_subsystem], message);
    return;
}

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

