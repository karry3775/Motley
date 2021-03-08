cmake_minimum_required(VERSION 3.0.2)

project(OpenGl_exploration)

find_package(glog REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

file(
    GLOB SOURCES_EXAMPLE_1
        "src/run_example1.cpp"
        "src/example1.cpp"
)

add_executable(example_1 ${SOURCES_EXAMPLE_1})
target_link_libraries(example_1 glog::glog  GLEW::GLEW glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_include_directories(
    example_1
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

