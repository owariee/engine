cmake_minimum_required(VERSION 3.19)

project(ice)

# Importing differrent libraries

find_package(PkgConfig REQUIRED) 
pkg_check_modules(fmt REQUIRED IMPORTED_TARGET fmt)

# Compile engine sub-modules

add_subdirectory(debug)
#add_subdirectory(graphics)
#add_subdirectory(sound)
#add_subdirectory(imgui)
#add_subdirectory(memory)
#add_subdirectory(vfs)
#add_subdirectory(window)

# Create engine executable

add_executable(ice main.cpp)
target_link_libraries(ice PUBLIC debug_lib)

