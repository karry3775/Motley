cmake_minimum_required(VERSION 3.0.2)

project(SDL_exploraation)


find_package(SDL2 REQUIRED)

add_executable(app src/sdl1.cpp)

target_link_libraries(app ${SDL2_LIBRARIES})

