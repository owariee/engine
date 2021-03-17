#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "FileInterface.hpp"

#include "glad/glad.h"

class Texture
{
    private:
        unsigned int id;
    public:
        Texture(FileInterface* file);
        ~Texture();
        void use(GLenum samplerPos);
};

#endif//TEXTURE_HPP