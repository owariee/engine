
add_library(debug_lib OBJECT Debug.cpp)

target_link_libraries(debug_lib fmt::fmt glad)
target_include_directories(debug_lib PUBLIC ./)

