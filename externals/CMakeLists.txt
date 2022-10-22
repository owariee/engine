if(DAWN_WITH_BUNDLED_GLAD)
        add_subdirectory(glad EXCLUDE_FROM_ALL)
        set(GLAD_FOUND 1 PARENT_SCOPE)
endif()

if(DAWN_WITH_BUNDLED_GLFW)
        set(GLFW_LIBRARY_TYPE "" CACHE STRING "" FORCE)
        add_subdirectory(glfw EXCLUDE_FROM_ALL)
        set(GLFW_FOUND 1 PARENT_SCOPE)
endif()

if(DAWN_WITH_BUNDLED_GLM)
        add_subdirectory(glm EXCLUDE_FROM_ALL)
        set(GLM_FOUND 1 PARENT_SCOPE)
endif()

if(DAWN_WITH_BUNDLED_IMGUI)
        add_library(imgui imgui/imgui.cpp
                          imgui/imgui_demo.cpp
                          imgui/imgui_draw.cpp
                          imgui/imgui_tables.cpp
                          imgui/imgui_widgets.cpp)
        target_include_directories(imgui PUBLIC ./imgui)
        set(IMGUI_FOUND 1 PARENT_SCOPE)
endif()

if(DAWN_WITH_BUNDLED_MINIZ)
        add_subdirectory(miniz EXCLUDE_FROM_ALL)
        set(MINIZ_FOUND 1 PARENT_SCOPE)
endif()

if(DAWN_WITH_BUNDLED_OPENAL)
        if(NOT BUILD_SHARED_LIBS)
                set(LIBTYPE STATIC CACHE STRING "" FORCE)
        endif()
        add_subdirectory(openal EXCLUDE_FROM_ALL)
        add_library(openal INTERFACE)
        target_link_libraries(openal INTERFACE OpenAL)
        set(OPENAL_FOUND 1 PARENT_SCOPE)
endif()

# vim:ts=8:sw=8:et:tw=100
