cmake_minimum_required(VERSION 3.0.2)

project(Ceres_exploration)

set(CMAKE_CXX_STANDARD 11)

find_package(glog REQUIRED)
find_package(Ceres REQUIRED)

file(
    GLOB SOURCES
        "src/main.cpp"
        "src/hello_world.cpp"
)

add_executable(hello_world ${SOURCES})
target_link_libraries(hello_world glog::glog Ceres::ceres)
target_include_directories(
    hello_world
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
