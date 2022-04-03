cmake_minimum_required(VERSION 3.16)

project(ice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Disable static building
set(BUILD_STATIC FALSE)

# Detect Linux environments
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Importing differrent libraries
add_subdirectory(externals)

# Set _DEBUG preprocessor macro if debug mode is set on Cmake
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

# Compile engine sub-modules
add_subdirectory(filesystem)
add_subdirectory(audio)
add_subdirectory(graphics)
add_subdirectory(window)

add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE graphics audio filesystem window)

add_subdirectory(game)
