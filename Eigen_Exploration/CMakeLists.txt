cmake_minimum_required(VERSION 3.0.2)

project(Eigen_Exploration)

find_package(glog REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(example src/example.cpp)
target_link_libraries(example Eigen3::Eigen glog::glog)
target_include_directories(
    example
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
