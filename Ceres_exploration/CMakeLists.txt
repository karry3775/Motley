cmake_minimum_required(VERSION 3.0.2)

project(Ceres_exploration)

set(CMAKE_CXX_STANDARD 11)

find_package(glog REQUIRED)
find_package(Ceres REQUIRED)


########### Hello world ##################################
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


############ Powell function ##############################
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

############### Curve fitting ###############################
file (
    GLOB SOURCES_CURVE_FITTING
        "src/run_curve_fitting.cpp"
        "src/curve_fitting.cpp"        
)

add_executable(curve_fitting ${SOURCES_CURVE_FITTING})
target_link_libraries(curve_fitting glog::glog Ceres::ceres)
target_include_directories(
    curve_fitting
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)


############## Robust curve fitting ##########################
file (
    GLOB SOURCES_ROBUST_CURVE_FITTING
        "src/run_robust_curve_fitting.cpp"
        "src/robust_curve_fitting.cpp"
)

add_executable(robust_curve_fitting ${SOURCES_ROBUST_CURVE_FITTING}) 
target_link_libraries(robust_curve_fitting glog::glog Ceres::ceres)
target_include_directories(
    robust_curve_fitting
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

############# Bundle adjustment ###############################
file (
    GLOB SOURCES_BUNDLE_ADJUSTMENT
        "src/run_bundle_adjustment.cpp"
        "src/bundle_adjustment.cpp"
)

add_executable(bundle_adjustment ${SOURCES_BUNDLE_ADJUSTMENT})
target_link_libraries(bundle_adjustment glog::glog Ceres::ceres) 
target_include_directories(
    bundle_adjustment
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

############### Robot pose MLE #################################
file (
    GLOB SOURCES_ROBOT_POSE_MLE
        "src/run_robot_pose_mle.cpp"
        "src/robot_pose_mle.cpp"
)

add_executable(robot_pose_mle ${SOURCES_ROBOT_POSE_MLE})
target_link_libraries(robot_pose_mle glog::glog Ceres::ceres)
target_include_directories(
    robot_pose_mle
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

############### Circle fit ######################################
file (
    GLOB SOURCES_CIRCLE_FIT
        "src/run_circle_fit.cpp"
        "src/circle_fit.cpp"
)

add_executable(circle_fit ${SOURCES_CIRCLE_FIT})
target_link_libraries(circle_fit glog::glog Ceres::ceres)
target_include_directories(
    circle_fit
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

########### test file ###########################################
file (
    GLOB SOURCES_TEST
        "src/test.cpp"
)

add_executable(test ${SOURCES_TEST})
target_link_libraries(test glog::glog Ceres::ceres)
target_include_directories (
    test
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)