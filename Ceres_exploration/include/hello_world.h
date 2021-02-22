#pragma once

#include "core.h"

// The problem at hand is to minimize
//   1          2
//  --- (10 - x)
//   2
// Comparing it to the problem formulation proposed
// by ceres we will get f(x) = (10 - x)

namespace hello_world {

// Functor for (10 - x)
struct CostFunctor;

// Function to formulate and solve the problem at hand
void solve();

}  // namespace hello_world