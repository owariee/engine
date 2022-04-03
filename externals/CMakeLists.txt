# Enable pkg-config in Linux environments
if(LINUX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
endif()

if(NOT GLFW_FOUND)
    add_subdirectory(glfw EXCLUDE_FROM_ALL)
endif()

set(LIBTYPE STATIC CACHE STRING "Static openal build" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build openal examples" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "Build openal config util" FORCE)
set(ALSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "Build openal version utility" FORCE)
add_subdirectory(openal-soft EXCLUDE_FROM_ALL)

add_subdirectory(glad EXCLUDE_FROM_ALL)
add_subdirectory(glm EXCLUDE_FROM_ALL)

add_library(imgui imgui/imgui.cpp
                  imgui/imgui_demo.cpp
                  imgui/imgui_draw.cpp
                  imgui/imgui_tables.cpp
                  imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ./imgui)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build miniz examples" FORCE)
add_subdirectory(miniz EXCLUDE_FROM_ALL)
