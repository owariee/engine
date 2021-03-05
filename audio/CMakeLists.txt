
add_library(audio STATIC AudioListener.cpp AudioSource.cpp)
target_link_libraries(audio PUBLIC OpenAL debug_lib filesystem)
target_include_directories(audio PUBLIC ./)
