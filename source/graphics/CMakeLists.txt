add_library(graphics STATIC Shader.cpp Mesh.cpp Camera3D.cpp Camera2D.cpp BMPLoader.cpp Texture.cpp
        Renderer2D.cpp)
target_link_libraries(graphics PUBLIC filesystem)
target_link_libraries(graphics PUBLIC glad glm window imgui)
target_include_directories(graphics PUBLIC ./)
