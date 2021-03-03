#ifndef VBO_HPP
#define VBO_HPP

#include "glad/glad.h"

#include <cstddef>

class VBO {

    public:
        enum DrawType { Stream = GL_STREAM_DRAW,
                        Static = GL_STATIC_DRAW,
                        Dynamic = GL_DYNAMIC_DRAW };
        VBO(void* data, std::size_t size, DrawType type = DrawType::Static);
        ~VBO();

        void bind();
        void unbind();
        void sendData(void* data, std::size_t size, DrawType type);
        void updateSubsetData(void* data, std::size_t size, long int offset);

    private:
        unsigned int buffer;

};

#endif//VBO_HPP
