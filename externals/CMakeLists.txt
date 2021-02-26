
add_subdirectory(fmt)
add_subdirectory(glfw)
#target_include_directories(glfw PUBLIC ./glfw/include)
add_subdirectory(openal-soft)
add_custom_command(OUTPUT "${OpenAL_BINARY_DIR}/OpenAL32.dll" COMMAND ${CMAKE_COMMAND} -E copy "${OpenAL_BINARY_DIR}/OpenAL32.dll" "${ice_BINARY_DIR}" DEPENDS ice)
add_custom_target(copy_files ALL DEPENDS "${ice_BINARY_DIR}/OpenAL32.dll")
add_subdirectory(glad)

add_library(imgui imgui/imgui.cpp
                  imgui/imgui_demo.cpp
                  imgui/imgui_draw.cpp
                  imgui/imgui_tables.cpp
                  imgui/imgui_widgets.cpp)

target_include_directories(imgui PUBLIC ./imgui)

add_library(lua lua/lapi.c 
                lua/lauxlib.c
                lua/lbaselib.c
                lua/lcode.c
                lua/lcorolib.c
                lua/lctype.c
                lua/ldblib.c
                lua/ldebug.c
                lua/ldo.c
                lua/ldump.c
                lua/lfunc.c
                lua/lgc.c
                lua/linit.c
                lua/liolib.c
                lua/llex.c
                lua/lmathlib.c
                lua/lmem.c
                lua/loadlib.c
                lua/lobject.c
                lua/lopcodes.c
                lua/loslib.c
                lua/lparser.c
                lua/lstate.c
                lua/lstring.c
                lua/lstrlib.c
                lua/ltable.c
                lua/ltablib.c
                lua/ltests.c
                lua/ltm.c
                lua/lua.c
                lua/lundump.c
                lua/lutf8lib.c
                lua/lvm.c
                lua/lzio.c
                lua/onelua.c)

target_include_directories(lua PUBLIC ./lua)

SET(BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
add_subdirectory(miniz)
