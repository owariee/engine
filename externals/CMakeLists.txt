add_subdirectory(glfw)

set(LIBTYPE STATIC ON CACHE BOOL "Static openal build" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build openal examples" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "Build openal config util" FORCE)
set(ALSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "Build openal version utility" FORCE)
add_subdirectory(openal-soft)

add_subdirectory(glad)
add_subdirectory(glm)

add_library(imgui imgui/imgui.cpp
                  imgui/imgui_demo.cpp
                  imgui/imgui_draw.cpp
                  imgui/imgui_tables.cpp
                  imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ./imgui)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build miniz examples" FORCE)
add_subdirectory(miniz)
