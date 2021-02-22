cmake_minimum_required(VERSION 3.0.2)

project(Ceres_exploration)

set(CMAKE_CXX_STANDARD 11)

find_package(glog REQUIRED)
find_package(Ceres REQUIRED)

file(
    GLOB SOURCES
        "src/main.cpp"
        "src/example_1.cpp"
)

add_executable(example_1 ${SOURCES})
target_link_libraries(example_1 glog::glog Ceres::ceres)
target_include_directories(
    example_1
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
