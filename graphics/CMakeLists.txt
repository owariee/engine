add_library(graphics OBJECT Graphics.cpp Mesh.cpp)

target_link_libraries(graphics PUBLIC glfw glad filesystem debug_lib)
target_include_directories(graphics PUBLIC ./)
