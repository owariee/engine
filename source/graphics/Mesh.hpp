#ifndef MESH_HPP
#define MESH_HPP


#include "glm/mat4x4.hpp"

#include <vector>
#include <string>

class Mesh
{
    private:
        unsigned int vertexArray;
        unsigned int vertexBuffer;
        unsigned int elementBuffer;

        glm::mat4 modelMatrix;

        uint32_t indiceNumber;
    public:
        Mesh(float* vertices, uint32_t verticeNumber, int* indices, uint32_t indiceNumber);
        ~Mesh();
        void draw();
        void setModelMatrix(glm::mat4 modelMatrix);
        glm::mat4 getModelMatrix();
};

#endif//MESH_HPP
