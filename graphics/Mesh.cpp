#include "Mesh.hpp"

Mesh::Mesh(FileInterface file)
{
    uint64_t size = file.getSize();
    while(file.tell() < size)
    {
        std::string line = Mesh::readLine(file);

        if (line[0] == 'v')
        {
            std::string vertexOne = line.substr(line.rfind(" ") + 1, line.length());
            std::string vertexTwo = vertexOne.substr(vertexOne.rfind(" ") + 1, vertexOne.length());
            vertexOne = vertexOne.substr(0, vertexOne.rfind(" "));
            std::string vertexThree = vertexTwo.substr(vertexTwo.rfind(" ") + 1, vertexTwo.length());
            vertexTwo = vertexTwo.substr(0, vertexTwo.find(" "));
        }
        else if (line[0] == 'f')
        {

        }
    }
    
    //load object from file
    //file.
    //create the VBO
    //create the VAO
    //create the EBO
}
Mesh::~Mesh()
{

}

void Mesh::draw()
{
    //establish the rule to draw the object
}

std::string Mesh::readLine(FileInterface file)
{
    std::string line = "";

    char temp = 'a';
    while(temp != '\n')
    {
        file.read(reinterpret_cast<uint8_t*>(&temp), 1);
        line += temp;
    }

    return line;
}

std::vector<std::string> Mesh::splitString(std::string line)
{
    std::vector<std::string> stringList;

    int oldPos = 0;
    int actualPos = 0;
    while (actualPos != std::string::npos)
    {
        actualPos = line.find(" ");
        stringList.push_back(line.substr(oldPos, actualPos));
    }

    return stringList;
}
