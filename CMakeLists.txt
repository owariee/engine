cmake_minimum_required(VERSION 3.16)

project(dawn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create LINUX variable if needed.
if(UNIX AND NOT APPLE)
        set(LINUX TRUE)
endif()

# Configure building type.
set(DAWN_WITH_BUNDLED_SHARED OFF CACHE BOOL "Enable shared linking of bundled libraries.")
set(BUILD_SHARED_LIBS ${DAWN_WITH_BUNDLED_SHARED} CACHE BOOL "" FORCE)

# Verify if user needs to compile any bundled library.
option(DAWN_WITH_BUNDLED_GLAD "Use bundled glad version (Windows only)" OFF)
option(DAWN_WITH_BUNDLED_GLFW "Use bundled glfw version (Windows only)" OFF)
option(DAWN_WITH_BUNDLED_GLM "Use bundled glm version (Windows only)" OFF)
option(DAWN_WITH_BUNDLED_IMGUI "Use bundled imgui version (Windows only)" OFF)
option(DAWN_WITH_BUNDLED_MINIZ "Use bundled miniz version (Windows only)" OFF)
option(DAWN_WITH_BUNDLED_OPENAL "Use bundled openal version (Windows only)" OFF)

# Configure building type for each bundled.
# set(DAWN_WITH_BUNDLED_GLAD_STATIC FALSE CACHE BOOL "Enable static linking for glad.")
# set(DAWN_WITH_BUNDLED_GLFW_STATIC FALSE CACHE BOOL "Enable static linking for glfw.")
# set(DAWN_WITH_BUNDLED_GLM_STATIC FALSE CACHE BOOL "Enable static linking for glm.")
# set(DAWN_WITH_BUNDLED_IMGUI_STATIC FALSE CACHE BOOL "Enable static linking for imgui.")
# set(DAWN_WITH_BUNDLED_MINIZ_STATIC FALSE CACHE BOOL "Enable static linking for miniz.")
# set(DAWN_WITH_BUNDLED_OPENAL_STATIC FALSE CACHE BOOL "Enable static linking for openal.")

# Manually set the path of the libraries.
set(DAWN_GLAD_LIBRARIES CACHE PATH "Path to the glad library")
set(DAWN_GLAD_INCLUDE_DIRS CACHE PATH "Path to the glad include directory")
set(DAWN_GLFW_LIBRARIES CACHE PATH "Path to the glfw library")
set(DAWN_GLFW_INCLUDE_DIRS CACHE PATH "Path to the glfw include directory")
set(DAWN_GLM_LIBRARIES CACHE PATH "Path to the glm library")
set(DAWN_GLM_INCLUDE_DIRS CACHE PATH "Path to the glm include directory")
set(DAWN_IMGUI_LIBRARIES CACHE PATH "Path to the imgui library")
set(DAWN_IMGUI_INCLUDE_DIRS CACHE PATH "Path to the imgui include directory")
set(DAWN_MINIZ_LIBRARIES CACHE PATH "Path to the miniz library")
set(DAWN_MINIZ_INCLUDE_DIRS CACHE PATH "Path to the miniz include directory")
set(DAWN_OPENAL_LIBRARIES CACHE PATH "Path to the openal library")
set(DAWN_OPENAL_INCLUDE_DIRS CACHE PATH "Path to the openal include directory")

# Configure manually-set library paths.
if(NOT DAWN_WITH_BUNDLED_GLAD)
        if("${DAWN_GLAD_LIBRARIES}" STREQUAL "" OR "${DAWN_GLAD_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(GLAD_LIBRARIES ${DAWN_GLAD_LIBRARIES})
                set(GLAD_INCLUDE_DIRS ${DAWN_GLAD_INCLUDE_DIRS})
                set(GLAD_FOUND 1)
        endif()
endif()

if(NOT DAWN_WITH_BUNDLED_GLFW)
        if("${DAWN_GLFW_LIBRARIES}" STREQUAL "" OR "${DAWN_GLFW_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(GLFW_LIBRARIES ${DAWN_GLFW_LIBRARIES})
                set(GLFW_INCLUDE_DIRS ${DAWN_GLFW_INCLUDE_DIRS})
                set(GLFW_FOUND 1)
        endif()
endif()

if(NOT DAWN_WITH_BUNDLED_GLM)
        if("${DAWN_GLM_LIBRARIES}" STREQUAL "" OR "${DAWN_GLM_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(GLM_LIBRARIES ${DAWN_GLM_LIBRARIES})
                set(GLM_INCLUDE_DIRS ${DAWN_GLM_INCLUDE_DIRS})
                set(GLM_FOUND 1)
        endif()
endif()

if(NOT DAWN_WITH_BUNDLED_IMGUI)
        if("${DAWN_IMGUI_LIBRARIES}" STREQUAL "" OR "${DAWN_IMGUI_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(IMGUI_LIBRARIES ${DAWN_IMGUI_LIBRARIES})
                set(IMGUI_INCLUDE_DIRS ${DAWN_IMGUI_INCLUDE_DIRS})
                set(IMGUI_FOUND 1)
        endif()
endif()

if(NOT DAWN_WITH_BUNDLED_MINIZ)
        if("${DAWN_MINIZ_LIBRARIES}" STREQUAL "" OR "${DAWN_MINIZ_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(MINIZ_LIBRARIES ${DAWN_MINIZ_LIBRARIES})
                set(MINIZ_INCLUDE_DIRS ${DAWN_MINIZ_INCLUDE_DIRS})
                set(MINIZ_FOUND 1)
        endif()
endif()

if(NOT DAWN_WITH_BUNDLED_OPENAL)
        if("${DAWN_OPENAL_LIBRARIES}" STREQUAL "" OR "${DAWN_OPENAL_INCLUDE_DIRS}" STREQUAL "")
        else()
                set(OPENAL_LIBRARIES ${DAWN_OPENAL_LIBRARIES})
                set(OPENAL_INCLUDE_DIRS ${DAWN_OPENAL_INCLUDE_DIRS})
                set(OPENAL_FOUND 1)
        endif()
endif()

# Configure any needed bundled library.
add_subdirectory(externals)

# Configure not bundled and not manually-set using pkg-config in Linux environments.
if(LINUX)
        find_package(PkgConfig REQUIRED)

        if(NOT GLAD_FOUND)
                pkg_check_modules(GLAD glad)
        endif()

        if(NOT GLFW_FOUND)
                pkg_check_modules(GLFW glfw3)
        endif()

        if(NOT GLM_FOUND)
                pkg_check_modules(GLM glm)
        endif()

        if(NOT IMGUI_FOUND)
                pkg_check_modules(IMGUI imgui)
        endif()

        if(NOT MINIZ_FOUND)
                pkg_check_modules(MINIZ miniz)
        endif()

        if(NOT OPENAL_FOUND)
                pkg_check_modules(OPENAL openal)
        endif()
endif()

# Configure not bundled and not manually-set using find_package.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(NOT GLAD_FOUND)
        find_package(glad REQUIRED)
endif()

if(NOT GLFW_FOUND)
        find_package(glfw3 REQUIRED)
endif()

if(NOT GLM_FOUND)
        find_package(glm REQUIRED)
endif()

if(NOT IMGUI_FOUND)
        find_package(imgui REQUIRED)
endif()

if(NOT MINIZ_FOUND)
        find_package(Miniz REQUIRED)
endif()

if(NOT OPENAL_FOUND)
        find_package(OpenAL REQUIRED)
endif()

# Create interfaces for each library.
if(GLAD_FOUND AND NOT DAWN_WITH_BUNDLED_GLAD)
        add_library(glad INTERFACE)
        target_link_libraries(glad INTERFACE ${GLAD_LIBRARIES})
        target_include_directories(glad INTERFACE ${GLAD_INCLUDE_DIRS})
endif()

if(GLFW_FOUND AND NOT DAWN_WITH_BUNDLED_GLFW)
        add_library(glfw INTERFACE)
        target_link_libraries(glfw INTERFACE ${GLFW_LIBRARIES})
        target_include_directories(glfw INTERFACE ${GLFW_INCLUDE_DIRS})
endif()

if(GLM_FOUND AND NOT DAWN_WITH_BUNDLED_GLM)
        add_library(glm INTERFACE)
        target_link_libraries(glm INTERFACE ${GLM_LIBRARIES})
        target_include_directories(glm INTERFACE ${GLM_INCLUDE_DIRS})
endif()

if(IMGUI_FOUND AND NOT DAWN_WITH_BUNDLED_IMGUI)
        add_library(imgui INTERFACE)
        target_link_libraries(imgui INTERFACE ${IMGUI_LIBRARIES})
        target_include_directories(imgui INTERFACE ${IMGUI_INCLUDE_DIRS})
endif()

if(MINIZ_FOUND AND NOT DAWN_WITH_BUNDLED_MINIZ)
        add_library(miniz INTERFACE)
        target_link_libraries(miniz INTERFACE ${MINIZ_LIBRARIES})
        target_include_directories(miniz INTERFACE ${MINIZ_INCLUDE_DIRS})
endif()

if(OPENAL_FOUND AND NOT DAWN_WITH_BUNDLED_OPENAL)
        add_library(openal INTERFACE)
        target_link_libraries(openal INTERFACE ${OPENAL_LIBRARIES})
        target_include_directories(openal INTERFACE ${OPENAL_INCLUDE_DIRS})
endif()

# On Windows, libraries:
# 1. Use DAWN_NAME_LIBRARIES and DAWN_NAME_INCLUDE_DIRS to create the interface. (Shared or Static)
# 2. Use find_package modules. (Shared)
# 3. Use bundled library. (Shared or Static)

# On Linux, libraries:
# 1. Use DAWN_NAME_LIBRARIES and DAWN_NAME_INCLUDE_DIRS to create the interface. (Shared or Static)
# Condition, if DAWN_NAME_BUNDLED == TRUE, jump to 4, otherwise continue
# 2. Use pkg_config. (Shared)
# 3. Use find_package modules. (Shared)
# 4. Use bundled library. (Shared or Static)

# Set _DEBUG preprocessor macro if debug mode is set on Cmake
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_DEBUG)
endif()

# Compile engine and sub-modules
add_subdirectory(source)

add_library(engine INTERFACE)
target_link_libraries(engine INTERFACE graphics audio filesystem window)

add_subdirectory(game)

# vim:ts=8:sw=8:et:tw=100
