#pragma once

#include "Grid.h"

namespace pathfinding {

class PathFinder {
   public:
    enum Method { DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS, DFS };
    PathFinder(PathFinder::Method method);
    void findPath(PathFinder::Method method);

   private:
    void findPathDijkstra();
    void findPathAstar();
    void findPathSample();
    void findPathHierarchical();
    void findPathBfs();
    void findPathDfs();

    Grid* grid_;
    Cell start_;
    Cell end_;
    PathFinder::Method method_;
};

}  // namespace pathfinding