add_library(graphics STATIC Shader.cpp Mesh.cpp Camera3D.cpp Camera2D.cpp BMPLoader.cpp Texture.cpp
        Renderer2D.cpp Window.cpp)
target_link_libraries(graphics PRIVATE glfw glad filesystem)
target_link_libraries(graphics PUBLIC glm)
target_include_directories(graphics PUBLIC ./)
