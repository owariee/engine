#include "Mesh.hpp"

Mesh::Mesh(float* vertices, uint32_t verticeNumber, int* indices, uint32_t indiceNumber)
: indiceNumber(indiceNumber)
{
    glGenVertexArrays(1, &(Mesh::vertexArray));
    glBindVertexArray(Mesh::vertexArray);

    glGenBuffers(1, &(Mesh::vertexBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, Mesh::vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticeNumber * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &(Mesh::elementBuffer));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh::elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceNumber * sizeof(int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Mesh::modelMatrix = glm::mat4(1.0f);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &(Mesh::vertexBuffer));
    glDeleteBuffers(1, &(Mesh::elementBuffer));
    glDeleteVertexArrays(1, &(Mesh::vertexArray));
}

void Mesh::draw()
{
    glBindVertexArray(Mesh::vertexArray);
    glDrawElements(GL_TRIANGLES, Mesh::indiceNumber, GL_UNSIGNED_INT, 0);
}

void Mesh::setModelMatrix(glm::mat4 modelMatrix)
{
    Mesh::modelMatrix = modelMatrix;
}

glm::mat4 Mesh::getModelMatrix()
{
    return Mesh::modelMatrix;
}
