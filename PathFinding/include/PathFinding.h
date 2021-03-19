#pragma once

#include "Grid.h"
#include "Maze.h"
#include "Visualization.h"

namespace pathfinding {

enum class PathFindingMethod { DIJKSTRA, ASTAR, SAMPLE, HIERARCHICAL, BFS };

// TODO: For future make this a template type so that it can support different
// varieties of cell (e.g. Square, pentagonal, hexagonal etc.)
class PathFinder {
   public:
    /**
     * @param env_type        Specify MAZE as environment type
     *
     * @param maze_gen_method Available methods to generate maze
     *                            [ RANDOMIZED_DFS, PRIMS and KRUSKALS ]
     *
     * @param pf_method       Method to be used for path finding
     *                        [DIJKSTRA, ASTAR, SAMPLE,
     *                        HIERARCHICAL, BFS]
     *
     * @param rows            Number of rows in the grid world
     * @param cols            Number of cols in the grid world
     * @param start           Starting Cell for the path
     * @param end             Ending Cell for the path
     *
     *
     */
    PathFinder(const EnvironmentType& env_type,
               const PathFindingMethod& pf_method,
               const MazeGenerationMethod& maze_gen_method,
               const uint32_t& rows, const uint32_t& cols,
               const uint32_t& cell_size, const Cell& start, const Cell& end,
               bool show_path_progression = true);

    /**
     * @param env_type        Specifiy GRID as the environment type
     *
     *
     * @param pf_method       Method to be used for path finding
     *                        Available options are DIJKSTRA, ASTAR, SAMPLE,
     *                        HIERARCHICAL, BFS
     *
     * @param obs_gen_method  Available methods to generate obstacles [MANUAL,
     *                        FISHER_YATES_SHUFFLE]
     *
     * @param obstacle_perc   Percentage of grid filled by obstacles
     *
     *
     * @param rows            Number of rows in the grid world
     * @param cols            Number of cols in the grid world
     * @param start           Starting Cell for the path
     * @param end             Ending Cell for the path
     *
     *
     */
    PathFinder(const EnvironmentType& env_type,
               const PathFindingMethod& pf_method,
               const ObstacleGenerationMethod& obs_gen_method,
               const double& obstacle_perc, const uint32_t& rows,
               const uint32_t& cols, const uint32_t& cell_size,
               const Cell& start, const Cell& end,
               bool show_path_progression = true);

    // TODO : Check if this is best way to return
    const Environment<Cell>* getEnvironment() const;

    const EnvironmentType& getEnvironmentType() const;

    const Path<Cell*> getPath() const;

    const std::vector<std::vector<int>> getObstacles() const;

    bool doesPathExists() const;

    void showFinalPath() const;

   private:
    bool findPath();
    bool findPathDijkstra();
    bool findPathAstar();
    bool findPathSample();
    bool findPathHierarchical();
    bool findPathBfs();

    void getPathFromPredecessorMap(const PredecessorMap<Cell*>& pred);

    Environment<Cell>* env_;
    Cell start_;
    Cell end_;
    PathFindingMethod pf_method_;
    EnvironmentType env_type_;

    Path<Cell*> path_;
    std::vector<std::vector<int>> obstacles_;
    bool path_found_;
    bool show_path_progression_;

    // Visualizer object
    std::unique_ptr<Visualizer> visualizer;
};

}  // namespace pathfinding