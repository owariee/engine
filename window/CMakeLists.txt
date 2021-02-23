
add_library(window OBJECT Window.cpp)
target_link_libraries(window PUBLIC glfw glad debug_lib)
target_include_directories(window PUBLIC ./)
