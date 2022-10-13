add_subdirectory(input)
add_library(window STATIC Window.cpp)
target_link_libraries(window PUBLIC filesystem graphics glad glfw input)
target_include_directories(window PUBLIC ./)