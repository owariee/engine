
add_library(graphics_gl OBJECT Shader.cpp)
target_link_libraries(graphics_gl PUBLIC glfw glad)
target_include_directories(graphics_gl PUBLIC ./)
