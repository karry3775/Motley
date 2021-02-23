#pragma once

#include "core.h"

namespace curve_fitting {

// Template object ot evaluate the residual
struct ExponentialResidual;

// Function to formulate and solve the problem
void solve(const std::vector<double>& x_data,
           const std::vector<double>& y_data);

}  // namespace curve_fitting