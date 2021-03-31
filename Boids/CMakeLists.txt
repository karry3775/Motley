cmake_minimum_required(VERSION 3.0.2)

project(Boids)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

find_package(glog REQUIRED)

file(
    GLOB SOURCES
        "src/Boids.cpp"
        "src/Visualization.cpp"
)

add_executable(BoidsApp src/BoidsApp.cpp ${SOURCES})
target_link_libraries(BoidsApp ${SDL2_LIBRARIES} glog::glog)
target_include_directories(
    BoidsApp
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)