#pragma once

#include "core.h"

namespace robot_pose_mle {

struct OdometryConstraint;

struct RangeConstraint;

// Return a random number sampled from a uniform distribution in the range
// [0, 1]
inline double RandDouble() {
    double r = static_cast<double>(rand());
    return r / RAND_MAX;
}

// Marsaglia Polar method for generating standard normal (pseudo)
// random numbers http://en.wikipedia.org/wiki/Marsaglia_polar_method
inline double RandNormal() {
    double x1, x2, w;
    do {
        x1 = 2.0 * RandDouble() - 1.0;
        x2 = 2.0 * RandDouble() - 1.0;
        w = x1 * x2 + x2 * x2;
    } while (w >= 1.0 || w == 0.0);

    w = sqrt((-2.0 * log(w)) / w);

    return x1 * w;
}

void simulateRobot(std::vector<double>* odometry_values,
                   std::vector<double>* range_readings);

void printState(const std::vector<double>& odometry_readings,
                const std::vector<double>& range_readings);

void solve(std::vector<double>& odometry_values,
           const std::vector<double>& range_readings);

}  // namespace robot_pose_mle