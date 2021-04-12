cmake_minimum_required(VERSION 3.0.2)

project(Pendulum)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

find_package(glog REQUIRED)

file(
    GLOB SOURCES
        "src/*.cpp"
)

add_executable(simple_pendulum src/simple_pendulum_app.cpp ${SOURCES})
target_link_libraries(simple_pendulum ${SDL2_LIBRARIES} glog::glog)
target_include_directories(
    simple_pendulum
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
