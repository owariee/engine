add_library(graphics STATIC Shader.cpp Mesh.cpp Camera3D.cpp Camera2D.cpp BMPLoader.cpp Texture.cpp
        Renderer2D.cpp Window.cpp)
target_link_libraries(graphics PUBLIC glfw filesystem)
target_link_libraries(graphics PUBLIC glad glm input)
target_include_directories(graphics PUBLIC ./)
