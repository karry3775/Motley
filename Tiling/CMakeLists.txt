cmake_minimum_required(VERSION 3.0.2)

project(Tiling)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(domino_tromino_tiling src/domino_tromino_tiling.cpp)
target_link_libraries(domino_tromino_tiling ${SDL2_LIBRARIES})
