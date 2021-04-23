#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "FileInterface.hpp"



class Texture
{
    private:
        unsigned int id;
    public:
        Texture(FileInterface* file);
        ~Texture();
        void use(unsigned int samplerPos);
};

#endif//TEXTURE_HPP