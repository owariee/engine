#include "VBO.hpp"

VBO::VBO(void* data, std::size_t size, VBO::DrawType type)
{
    glGenBuffers(1, &(VBO::buffer));

    VBO::bind();
    VBO::sendData(data, size, type);
    VBO::unbind();
}
VBO::~VBO()
{
    glDeleteBuffers(1, &(VBO::buffer));
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO::buffer);
}
void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::sendData(void* data, std::size_t size, DrawType type)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, type);
}
void VBO::updateSubsetData(void* data, std::size_t size, long int offset)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}
