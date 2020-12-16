#include "debug/Debug.hpp"
#include "fmt/color.h"
#include "fmt/core.h"

int main(int argc, char* argv[]) 
{
    Debug::print(6, Debug::Subsystem::Memory, "A memoria esta sendo estourada");
    return 0;
}


