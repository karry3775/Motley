cmake_minimum_required(VERSION 3.0.2)

project(AntColonySimulation)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

find_package(glog REQUIRED)

file (
    GLOB SOURCES
        "src/AntColonySimulation.cpp"
        "src/Utils.cpp"
        "src/Defaults.cpp"
)

add_executable(AntColonyApp src/AntColonyApp.cpp ${SOURCES})
target_link_libraries(AntColonyApp ${SDL2_LIBRARIES} glog::glog)
target_include_directories(
    AntColonyApp
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

