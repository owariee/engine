#include "Mesh.hpp"

Mesh::Mesh(float* vertices, uint32_t verticeNumber, int* indices, uint32_t indiceNumber)
{
    glGenVertexArrays(1, &(Mesh::vertexArray));
    glBindVertexArray(Mesh::vertexArray);

    glGenBuffers(1, &(Mesh::vertexBuffer));
    glBindBuffer(GL_ARRAY_BUFFER, Mesh::vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, verticeNumber * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &(Mesh::elementBuffer));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh::elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceNumber * sizeof(int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
