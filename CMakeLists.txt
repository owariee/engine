cmake_minimum_required(VERSION 3.18)

project(ice)

# Importing differrent libraries
add_subdirectory(externals)

# Set _DEBUG preprocessor macro if debug mode is set on Cmake
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# Compile engine sub-modules

add_subdirectory(debug)
add_subdirectory(memory)
add_subdirectory(graphics)
#add_subdirectory(sound)
#add_subdirectory(imgui)
#add_subdirectory(vfs)
add_subdirectory(window)

# Create engine executable

add_executable(ice main.cpp)
target_link_libraries(ice PUBLIC debug_lib memory graphics window)


