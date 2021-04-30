add_library(input STATIC Gamepad.cpp Keyboard.cpp Mouse.cpp Input.cpp)
target_link_libraries(input PUBLIC graphics glfw)
target_include_directories(input PUBLIC ./)
