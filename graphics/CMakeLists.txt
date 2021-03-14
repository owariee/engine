add_library(graphics OBJECT Shader.cpp Mesh.cpp Camera3D.cpp Camera2D.cpp)

target_link_libraries(graphics PUBLIC glfw glad glm filesystem debug_lib window)
target_include_directories(graphics PUBLIC ./)
