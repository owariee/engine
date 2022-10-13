#ifndef WAVEFRONTOBJECTLOADER_HPP
#define WAVEFRONTOBJECTLOADER_HPP

#include "FileInterface.hpp"

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <vector>

class WavefrontObjectLoader
{
    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> textureCoords;
        //std::vector<uint32_t> indices;
        //std::vector<uint32_t> textureCoordIndices;
        //std::vector<uint32_t> normalIndices;

        int verifyOcurrences(std::string component);
    public:
        WavefrontObjectLoader(FileInterface* file);
        ~WavefrontObjectLoader();
        
};

#endif//WAVEFRONTOBJECTLOADER_HPP