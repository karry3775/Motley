#include "PathFinding.h"

namespace PF = pathfinding;

int main(int argc, char** argv) {
    // TODO: Make the function call more abstract for
    // the end user
    // Number of rows in the grid
    uint32_t rows{10};

    // Number of cols in the grid
    uint32_t cols{20};

    // Size of individual cell in pixels
    uint32_t cell_size{50};

    // Choose a starting point
    PF::Cell start(3, 3);

    // Choose an ending point
    PF::Cell end(9, 19);

    std::unique_ptr<PF::PathFinder> grid_path_finder(new PF::PathFinder(
        PF::EnvironmentType::GRID, PF::PathFindingMethod::DIJKSTRA,
        PF::ObstacleGenerationMethod::FISHER_YATES_SHUFFLE,
        /**obstacle percentage**/ 0.1, rows, cols, cell_size, start, end,
        false));

    grid_path_finder->showFinalPath();

    // Create a maze PathFinder Object
    std::unique_ptr<PF::PathFinder> maze_path_finder(new PF::PathFinder(
        PF::EnvironmentType::MAZE, PF::PathFindingMethod::DIJKSTRA,
        PF::MazeGenerationMethod::RANDOMIZED_DFS, rows, cols, cell_size, start,
        end, false));

    maze_path_finder->showFinalPath();

    return 0;
}