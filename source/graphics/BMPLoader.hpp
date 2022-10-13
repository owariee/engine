#ifndef BMPLOADER_HPP
#define BMPLOADER_HPP

#include "FileInterface.hpp"

#include "glad/glad.h"
#include "glm/vec2.hpp"

class BMPLoader
{
    private:
        struct BMPHeader
        {
            uint32_t imageOffset;
            uint32_t dibHDRSize;
            uint32_t width;
            uint32_t height;
            uint16_t planes;
            uint16_t bitsPerPixel;
            uint32_t compress;
            uint32_t imageSize;
        } bmpHeader;

        char* imageData;
    public:
        BMPLoader(FileInterface* file);
        ~BMPLoader();

        glm::vec2 getImageResolution();
        GLenum getImageFormat();
        char* getImageData();
};

#endif//BMPLOADER_HPP