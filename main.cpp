#define _DEBUG

#include "debug/Debug.hpp"

int main(int argc, char* argv[]) 
{
    Debug::print(Debug::Flags::Error, Debug::Subsystem::Memory, "Memory overflow!");
    return 0;
}


