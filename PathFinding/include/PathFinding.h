#pragma once

#include "Grid.h"

namespace pathfinding {

class PathFinder {
   public:
    enum Method { DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS };
    /**
     * @param rows   Number of rows in the grid world
     * @param cols   Number of cols in the grid world
     * @param start  Starting Cell for the path
     * @param end    Ending Cell for the path
     * @param method Method to be used for path finding
     * Available options are DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS, DFS
     */
    PathFinder(uint32_t rows, uint32_t cols, Cell start, Cell end,
               PathFinder::Method method);

   private:
    void findPath();
    void findPathDijkstra();
    void findPathAstar();
    void findPathSample();
    void findPathHierarchical();
    void findPathBfs();

    Grid* grid_;
    Cell start_;
    Cell end_;
    PathFinder::Method method_;

    Path<Cell> path_;
};

}  // namespace pathfinding