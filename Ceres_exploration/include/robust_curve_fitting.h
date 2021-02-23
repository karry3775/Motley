#pragma once

#include "core.h"

namespace robust_curve_fitting {

struct ExponentialResidual;

void solve(const std::vector<double>& x_data,
           const std::vector<double>& y_data);

}  // namespace robust_curve_fitting
