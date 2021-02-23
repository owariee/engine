add_subdirectory(opengl)

add_library(graphics OBJECT Graphics.cpp)

target_link_libraries(graphics PUBLIC graphics_gl glfw glad debug_lib)
target_include_directories(graphics PUBLIC ./)
