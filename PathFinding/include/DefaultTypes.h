#pragma once

#include "Core.h"
#include "Wall.h"

namespace pathfinding {

// TODO: Migrate to unordered_map
template <typename T>
using AdjacencyList = std::map<T, std::vector<T>>;

template <typename T>
using Path = std::vector<T>;

template <typename T>
using PredecessorMap = std::map<T, T>;

template <typename T>
using DistanceMap = std::map<T, int>;

}  // namespace pathfinding