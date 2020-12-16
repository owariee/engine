#include "Debug.hpp"
#include "fmt/core.h"
#include "fmt/color.h"
#include <iostream>

#ifdef __DEBUG

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
    fmt::print(fg(color), "{}::{}: {}.",type, subsystem[index_subsystem], message);
    return;
}

#else

void Debug::print(int flag, int index_subsystem, std::string message) 
{
    return;
}

#endif

