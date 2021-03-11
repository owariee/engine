#ifndef MESH_HPP
#define MESH_HPP

#include "glad/glad.h"

#include <vector>
#include <string>

class Mesh
{
    private:
        unsigned int vertexArray;
        unsigned int vertexBuffer;
        unsigned int elementBuffer;
    public:
        Mesh(float* vertices, uint32_t verticeNumber, int* indices, uint32_t indiceNumber);
        ~Mesh();
        void draw();
};

#endif//MESH_HPP
