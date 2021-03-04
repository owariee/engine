#ifndef SHADER_HPP
#define SHADER_HPP

#include "FileInterface.hpp"

#include <vector>
#include <string>

class Mesh
{
    public:
        Mesh(FileInterface file);
        ~Mesh();

        void draw();
    
    private:
        std::string readLine(FileInterface file);
        std::vector<std::string> splitString(std::string line);
};

#endif//SHADER_HPP
