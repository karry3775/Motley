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

template <typename T1, typename T2>
using MinHeap =
    std::priority_queue<std::pair<T1, T2>, std::vector<std::pair<T1, T2>>,
                        std::greater<std::pair<T1, T2>>>;

enum class EnvironmentType { GRID, MAZE };
}  // namespace pathfinding