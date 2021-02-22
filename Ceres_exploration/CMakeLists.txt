cmake_minimum_required(VERSION 3.0.2)

project(Ceres_exploration)

set(CMAKE_CXX_STANDARD 11)

find_package(glog REQUIRED)
find_package(Ceres REQUIRED)

file(
    GLOB SOURCES_HELLO_WORLD
        "src/run_hello_world.cpp"
        "src/hello_world.cpp"
)
# Alternative way
# set(
#     SOURCES_HELLO_WORLD 
#     ${PROJECT_SOURCE_DIR}/src/run_hello_world.cpp 
#     ${PROJECT_SOURCE_DIR}/src/hello_world.cpp 
# )

add_executable(hello_world ${SOURCES_HELLO_WORLD})
target_link_libraries(hello_world glog::glog Ceres::ceres)
target_include_directories(
    hello_world
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

file(
    GLOB SOURCES_POWELL
        "src/run_powell.cpp"
        "src/powell_function.cpp"
)

# Alternative way
# set(
#     SOURCES_POWELL
#     ${PROJECT_SOURCE_DIR}/src/run_powell.cpp 
#     ${PROJECT_SOURCE_DIR}/src/powell_function.cpp 
# )



add_executable(powell ${SOURCES_POWELL})
target_link_libraries(powell glog::glog Ceres::ceres)
target_include_directories(
    powell
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
