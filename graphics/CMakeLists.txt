add_library(graphics OBJECT Shader.cpp Mesh.cpp Camera3D.cpp Camera2D.cpp BMPLoader.cpp Texture.cpp Renderer2D.cpp Window.cpp)
add_library(teste )

target_link_libraries(graphics PUBLIC glfw glad glm filesystem debug_lib)
target_include_directories(graphics PUBLIC ./)
