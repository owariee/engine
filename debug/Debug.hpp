#pragma once

#include <string>

namespace Debug 
{
    typedef enum { Error, Warning, Info, Trace } Flags;
    typedef enum { Debug, Memory, Graphics, Vfs, Sound, Window, Gui, Lua } Subsystem;

    void print(int flag, int subsystem, std::string message);

};

