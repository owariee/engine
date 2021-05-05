add_library(filesystem STATIC FileInfo.cpp FileNative.cpp FilesystemNative.cpp FileZip.cpp
        FilesystemZip.cpp LineArgumentParser.cpp)
target_link_libraries(filesystem PUBLIC miniz)
target_include_directories(filesystem PUBLIC ./)
