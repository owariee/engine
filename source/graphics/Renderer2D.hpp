#ifndef RENDERER2D_HPP
#define RENDERER2D_HPP

#include "FilesystemInterface.hpp"

#include "Camera2D.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"


#include "glm/glm.hpp"

#include <vector>

class Renderer2D
{
    private:        
        Mesh* mesh;
        Shader* shader;

    public:
        Camera2D* camera;

        Renderer2D(int width, int height, FilesystemInterface* fs);
        ~Renderer2D();

        void drawRectangle(int x, int y, int width, int height, glm::vec3 color);
};

#endif//RENDERER2D_HPP