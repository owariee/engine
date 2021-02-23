
add_library(filesystem OBJECT FileInfo.cpp FileNative.cpp FilesystemNative.cpp FilesystemLZ4.cpp)

target_link_libraries(filesystem debug_lib microtar)
target_include_directories(filesystem PUBLIC ./)

