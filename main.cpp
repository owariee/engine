#include "debug/Debug.hpp"

int main(int argc, char* argv[]) 
{
    Debug::print(6, Debug::Subsystem::Memory, "Memory overflow!");
    return 0;
}


