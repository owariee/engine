#ifndef SHADER_HPP
#define SHADER_HPP

#include "FileInterface.hpp"

class Mesh
{
    Mesh(FileInterface file);
    ~Mesh();

    void draw();
};

#endif//SHADER_HPP
