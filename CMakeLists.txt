cmake_minimum_required(VERSION 3.18)

project(ice)

# Importing differrent libraries
if(UNIX)
    find_package(PkgConfig REQUIRED) 
    pkg_check_modules(fmt REQUIRED IMPORTED_TARGET fmt)
    pkg_check_modules(glfw REQUIRED IMPORTED_TARGET glfw3)
    pkg_check_modules(glew REQUIRED IMPORTED_TARGET glew)
elseif(WIN32)
    add_subdirectory(externals)
endif()

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
target_link_libraries(ice PUBLIC fmt)



