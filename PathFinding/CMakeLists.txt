cmake_minimum_required(VERSION 3.0.2)

project(PathFinding)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

find_package(glog REQUIRED)

file(
    GLOB SOURCES
        "src/main.cpp"
        "src/Grid.cpp"
        "src/PathFinding.cpp"
        "src/Visualization.cpp"
        "src/Maze.cpp"
        "src/Wall.cpp"
)

add_executable(path_finding ${SOURCES})
target_link_libraries(path_finding ${SDL2_LIBRARIES} glog::glog)
target_include_directories(
    path_finding
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


############ Examples (TODO rename these to be specfic) #################
file(
    GLOB SOURCES_TEST
        "examples/example1.cpp"
        "src/Grid.cpp"
        "src/PathFinding.cpp"
        "src/Visualization.cpp"
        "src/Maze.cpp"
        "src/Wall.cpp"
)

add_executable(example1 ${SOURCES_TEST})
target_link_libraries(example1 ${SDL2_LIBRARIES} glog::glog)
target_include_directories(
    example1
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
