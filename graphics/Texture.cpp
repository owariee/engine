#include "Texture.hpp"

#include "BMPLoader.hpp"

Texture::Texture(FileInterface* file)
{
    glGenTextures(1, &(Texture::id));
    glBindTexture(GL_TEXTURE_2D, Texture::id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    BMPLoader* bmpLoader = new BMPLoader(file);
    glm::vec2 res = bmpLoader->getImageResolution();

    GLenum format = bmpLoader->getImageFormat();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res.x, res.y, 0,
        format, GL_UNSIGNED_BYTE, bmpLoader->getImageData());
    glGenerateMipmap(GL_TEXTURE_2D);

    delete bmpLoader;
}

Texture::~Texture()
{
    glDeleteTextures(1, &(Texture::id));
}

void Texture::use(GLenum samplerPos)
{
    glActiveTexture(samplerPos);
    glBindTexture(GL_TEXTURE_2D, Texture::id);
}
