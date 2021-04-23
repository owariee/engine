#include "Renderer2D.hpp"

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_transform.hpp"

Renderer2D::Renderer2D(int width, int height, FilesystemInterface* fs)
{
    FileInfo vertexShaderPath("renderer2d.vs");
    FileInterface* vertexFile = fs->openFile(vertexShaderPath, FileInterface::Mode::Read);
    FileInfo fragmentShaderPath("renderer2d.fs");
    FileInterface* fragmentFile = fs->openFile(fragmentShaderPath, FileInterface::Mode::Read);
    Renderer2D::shader = new Shader(vertexFile, fragmentFile);

    Renderer2D::camera = new Camera2D(width, height);

    float vertices[] = 
    {
        // width + x,      y
        // width + x, height + y
        // x,         height + y
        // x,              y
          1.0f,  0.0f, 0.0f, 1.0f, 1.0f, // top right
          1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // bottom right
          0.0f,  1.0f, 0.0f, 0.0f, 0.0f, // bottom left
          0.0f,  0.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    int indices[] = 
    {
        0, 1, 3,
        1, 2, 3
    };

    Renderer2D::mesh = new Mesh(vertices, 20, indices, 6);
}

Renderer2D::~Renderer2D()
{
    delete Renderer2D::camera;
    delete Renderer2D::mesh;
    delete Renderer2D::shader;
}

void Renderer2D::drawRectangle(int x, int y, int width, int height, glm::vec3 color)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::scale(model, glm::vec3(width, height, 0.0f));
    Renderer2D::mesh->setModelMatrix(model);

    Renderer2D::shader->use();
    Renderer2D::shader->setUniform("objectColor", color);
    Renderer2D::shader->setUniform("cameraMatrix", Renderer2D::camera->getViewMatrix());
    Renderer2D::shader->setUniform("modelMatrix",  Renderer2D::mesh->getModelMatrix());
    Renderer2D::mesh->draw();
}
