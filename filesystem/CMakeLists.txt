
add_library(filesystem OBJECT FileInfo.cpp FileNative.cpp FilesystemNative.cpp FileZip.cpp FilesystemZip.cpp LineArgumentParser.cpp)

target_link_libraries(filesystem debug_lib miniz)
target_include_directories(filesystem PUBLIC ./)

