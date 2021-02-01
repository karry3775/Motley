#pragma once

#include "Core.h"

namespace pathfinding {

template <typename T>
using AdjacencyList = std::map<T, std::vector<T>>;

}  // namespace pathfinding