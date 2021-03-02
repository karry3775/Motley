#include <robot_pose_mle.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    
    std::vector<double> odometry_values;
    std::vector<double> range_readings;

    // This step is populating the values for odometry and
    // range readings by simulation
    robot_pose_mle::simulateRobot(&odometry_values, &range_readings);

    // Lets print the initial values
    LOG(INFO) << "Initial values";
    robot_pose_mle::printState(odometry_values, range_readings);

    robot_pose_mle::solve(odometry_values, range_readings);

    return 0;
}