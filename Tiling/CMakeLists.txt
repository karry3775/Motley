cmake_minimum_required(VERSION 3.0.2)

project(Tiling)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

file(
    GLOB SOURCES
        "src/Tiling.cpp"
)

add_executable(domino_tromino_tiling src/domino_tromino_tiling.cpp ${SOURCES})
target_link_libraries(domino_tromino_tiling ${SDL2_LIBRARIES})
target_include_directories(
    domino_tromino_tiling
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

