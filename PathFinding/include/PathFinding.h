#pragma once

#include "Grid.h"
#include "Maze.h"

namespace pathfinding {

enum class Method { DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS };
enum class EnvironmentType { GRID, MAZE };

// TODO: For future make this a template type so that it can support different
// varieties of cell (e.g. Square, pentagonal, hexagonal etc.)
class PathFinder {
   public:
    /**
     * @param env_type     Choice of environment to perform path finding
     *                     Available options are GRID and MAZE
     *
     * @param gen_method   Available methods to generate the environment
     *                     For Maze: RANDOMIZED_DFS, PRIMS and KRUSKALS
     *                     are Needed. For Grid: NONE suffices as no method
     *                     is needed
     *
     * @param method       Method to be used for path finding
     *                     Available options are DIJKSTRA, ASTAR, SAMPLE,
     *                     HIERARCHICAL, BFS
     *
     * @param rows         Number of rows in the grid world
     * @param cols         Number of cols in the grid world
     * @param start        Starting Cell for the path
     * @param end          Ending Cell for the path
     *
     *
     */
    PathFinder(const EnvironmentType& env_type, const Method& method,
               const GenerationMethod& gen_method, const uint32_t& rows,
               const uint32_t& cols, const uint32_t& cell_size,
               const Cell& start, const Cell& end);

    // TODO : Check if this is best way to return
    const Environment<Cell>* getEnvironment() const;

    const EnvironmentType& getEnvironmentType() const;

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