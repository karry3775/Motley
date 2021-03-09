cmake_minimum_required(VERSION 3.0.2)

project(OpenGl_exploration)

find_package(glog REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)


########### example 1 ##################################
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

############### triangle ##############################
add_executable(triangle src/triangle.cpp)
target_link_libraries(triangle glog::glog GLEW::GLEW glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_include_directories(
    triangle
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)

############## colored cube ################################
add_executable(colored_cube src/colored_cube.cpp src/shader.cpp)
target_link_libraries(colored_cube glog::glog GLEW::GLEW glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_include_directories(
    colored_cube
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)


############# textured cube ###################################
add_executable(textured_cube src/textured_cube.cpp src/shader.cpp src/texture.cpp)
target_link_libraries(textured_cube glog::glog GLEW::GLEW glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_include_directories(
    textured_cube
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include 
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
)
