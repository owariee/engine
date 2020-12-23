#include "Graphics.hpp"

#include "../debug/Debug.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"


Graphics::Graphics()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Debug::print(Debug::Flags::Error,
                     Debug::Subsystem::Graphics,
                     "Failed to initialize Graphics Subsystem");
        return;
    }
}

Graphics::~Graphics()
{
    return;
}

    //todo
    //Property a = 
    //{
    //  albedo color (rgba) or texture
    //  metallic range
    //      metallic smoothness
    //  normal map (most recognized as the new better bump map, it uses rgb instead of grayscale)
    //  height map
    //  occlusion map
    //  emission map
    //  detail mask
    // tiling x and y
    // offset x and y
    //}
    //Material teste = gfx.Materials.create(Property prop);
