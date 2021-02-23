
add_library(memory OBJECT Memory.cpp)
target_link_libraries(memory PUBLIC debug_lib)
target_include_directories(memory PUBLIC ./)
