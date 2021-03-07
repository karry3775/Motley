#pragma once

#include "core.h"

namespace circle_fit {

struct CircleFitCostFunction {
    // Cost function
    CircleFitCostFunction(double x, double y);

    // Residual
    template <typename T>
    bool operator()(const T* const cx, const T* const cy, const T* const m,
                    T* residual) const {
        // Equation of circle
        // (x - cx)^2 + (y - cy)^2 = r^2;
        // residual = r^2 - (x - cx)^2 - (y - cy)^2;
        T r = m[0] * m[0];
        residual[0] =
            r * r - (x - cx[0]) * (x - cx[0]) - (y - cy[0]) * (y - cy[0]);
        return true;
    }

    // Factory function to hide the creation of the above cost
    // function
    static ceres::CostFunction* create(double x, double y);

   private:
    double x, y;
};

void generateData(std::vector<double>& x_data, std::vector<double>& y_data,
                  double radius, double cx, double cy, double noise_perc,
                  double theta_resolution);

void solve(const std::vector<double>& x_data, const std::vector<double>& y_data,
           double& cx, double& cy, double& radius);

}  // namespace circle_fit