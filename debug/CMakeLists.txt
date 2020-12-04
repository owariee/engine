
add_library(debug_lib OBJECT Debug.cpp)

if(UNIX)
	target_link_libraries(debug_lib PUBLIC PkgConfig::fmt)
elseif(WIN32)
	target_link_libraries(debug_lib fmt::fmt)
endif()

