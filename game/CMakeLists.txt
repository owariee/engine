add_executable(game main.cpp)
target_link_libraries(game PUBLIC engine)

install(TARGETS game DESTINATION /usr/bin)
