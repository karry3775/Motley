#pragma once

#include "Grid.h"
#include "Maze.h"

namespace pathfinding {

enum class Method { DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS };
enum class EnvironmentType { GRID, MAZE };

class PathFinder {
   public:
    /**
     * @param rows   Number of rows in the grid world
     * @param cols   Number of cols in the grid world
     * @param start  Starting Cell for the path
     * @param end    Ending Cell for the path
     * @param method Method to be used for path finding
     * Available options are DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS
     * @param env    Choice of environment to perform path finding
     * Available options are GRID and MAZE
     */
    PathFinder(const uint32_t& rows, const uint32_t& cols,
               const uint32_t& cell_size, const Cell& start, const Cell& end,
               const Method& method, const EnvironmentType& env_type);

    // TODO : Check if this is best way to return
    const Environment<Cell>* getEnvironment() const;

    const Path<Cell*> getPath() const;

   private:
    void findPath();
    void findPathDijkstra();
    void findPathAstar();
    void findPathSample();
    void findPathHierarchical();
    void findPathBfs();

    Environment<Cell>* env_;
    Cell start_;
    Cell end_;
    Method method_;
    EnvironmentType env_type_;

    Path<Cell*> path_;
};

}  // namespace pathfinding