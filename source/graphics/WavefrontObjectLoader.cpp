#include "WavefrontObjectLoader.hpp"

#include "Debug.hpp"

#include <string>
#include <strstream>

WavefrontObjectLoader::WavefrontObjectLoader(FileInterface* file)
{
    if(!(file->isOpen()))
    {
        Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
            "The BMP file must be open for reading.");
        return;
    }

    char tmp = ' ';
    while(tmp != '\0' || file->tell() < file->getSize())
    {
        std::string line = "";

        if (tmp == '\n')
        {
            tmp = ' ';
        }

        while(tmp != '\n')
        {
            file->read(reinterpret_cast<uint8_t*>(&tmp), sizeof(char));
            line += tmp;
        }

        std::strstream s;
        s << line;

        char junk;

        if (line[0] == 'v')
        {
            glm::vec3 vector;
            s >> junk >> vector.x >> vector.y >> vector.z;
            WavefrontObjectLoader::vertices.push_back(vector);
        }
        else if (line[0] == 'v' && line[1] == 't')
        {
            glm::vec3 textureCoord;
            s >> junk >> textureCoord.x >> textureCoord.y >> textureCoord.z;
            WavefrontObjectLoader::textureCoords.push_back(textureCoord);
        }
        // else if (line[0] == 'f')
        // {
        //     std::string indices[3];
        //     s >> junk >> indices[0] >> indices[1] >> indices[2];

        //     int pastOcurrences = 0;
        //     for(int i = 0; i < 3; i++)
        //     {
        //         int actualOcurrences = verifyOcurrences(indices[i]);
        //         if (actualOcurrences == 0)
        //         {
        //             WavefrontObjectLoader::indices.push_back(std::stoi(indices[i]) - 1);
        //         }
        //         else if (actualOcurrences == 1)
        //         {
        //             auto firstSlash = indices[i].find( "/" );
        //             //WavefrontObjectLoader::indices.push_back(std::stoi(indices[i].substr(0, firstSlash)));
        //             //WavefrontObjectLoader::texturePos.push_back(std::stoi(indices[i].substr(firstSlash, indices[i].length() - 1)));
        //         }
        //         else if (actualOcurrences == 2)
        //         {
        //             auto firstSlash = indices[i].find( "/" );
        //             WavefrontObjectLoader::indices.push_back(std::stoi(indices[i].substr(0, firstSlash)));
        //             auto secondSlash = indices[i].rfind( "/" );
        //             //WavefrontObjectLoader::texturePos.push_back(std::stoi(indices[i].substr(firstSlash, secondSlash)));
        //             //WavefrontObjectLoader::normals.push_back(std::stoi(indices[i].substr(secondSlash, indices[i].length() - 1)));
        //         }
        //         else
        //         {
        //             Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
        //                 "Inconsistent Wavefront Object File, component has more than 3 informations");
        //         }

        //         if (pastOcurrences != actualOcurrences)
        //         {
        //             Debug::print(Debug::Flags::Error, Debug::Subsystem::Graphics,
        //                 "Inconsistent Wavefront Object File, difference between components");
        //         }
                
        //         pastOcurrences = actualOcurrences;
        //     }
        }
    }
}

WavefrontObjectLoader::~WavefrontObjectLoader()
{

}

int WavefrontObjectLoader::verifyOcurrences(std::string component)
{
    int count = 0;
    for(auto i = component.begin(); i != component.end(); i++)
    {
        if(*i == '/')
        {
            count++;
        }
    }
    return count;
}