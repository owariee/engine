# Enable pkg-config in Linux environments
if(UNIX AND NOT BUILD_STATIC)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW glfw3)
    if(GLFW_FOUND)
        add_library(glfw INTERFACE)
        target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})
    endif()
    pkg_check_modules(OPENAL openal)
    if(OPENAL_FOUND)
        add_library(openal INTERFACE)
        target_link_libraries(openal INTERFACE ${OPENAL_LIBRARIES})
    endif()
    pkg_check_modules(GLM glm)
    if(GLM_FOUND)
        add_library(glm INTERFACE)
        target_link_libraries(glm INTERFACE ${GLM_LIBRARIES})
    endif()
endif()

if(NOT GLFW_FOUND)
    if(NOT BUILD_STATIC)
        set(BUILD_SHARED_LIBS ON CACHE BOOL "Build glfw dinamically" FORCE)
    endif()
    add_subdirectory(glfw EXCLUDE_FROM_ALL)
endif()

if(NOT OPENAL_FOUND)
    if(BUILD_STATIC)
        set(LIBTYPE STATIC CACHE STRING "Build openal statically" FORCE)
    endif()
    set(ALSOFT_EXAMPLES OFF CACHE BOOL "Build openal examples" FORCE)
    set(ALSOFT_UTILS OFF CACHE BOOL "Build openal config util" FORCE)
    set(ALSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "Build openal version utility" FORCE)
    add_subdirectory(openal-soft EXCLUDE_FROM_ALL)
    add_library(openal INTERFACE)
    target_link_libraries(openal INTERFACE OpenAL)
endif()

add_subdirectory(glad EXCLUDE_FROM_ALL)

if(NOT GLM_FOUND)
    add_subdirectory(glm EXCLUDE_FROM_ALL)
endif()

add_library(imgui imgui/imgui.cpp
                  imgui/imgui_demo.cpp
                  imgui/imgui_draw.cpp
                  imgui/imgui_tables.cpp
                  imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC ./imgui)

set(BUILD_EXAMPLES OFF CACHE BOOL "Build miniz examples" FORCE)
add_subdirectory(miniz EXCLUDE_FROM_ALL)
