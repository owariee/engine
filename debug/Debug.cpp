#include "Debug.hpp"
#include "fmt/core.h"
#include <iostream>


void Debug::print(std::string message) {
    std::cout << message << "\n";
    fmt::print("I'd rather be {1} than {0}.", "right", "happy");
    return;
}







