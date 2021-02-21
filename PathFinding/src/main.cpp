#include "Visualization.h"
#include "PathFinding.h"

namespace PF = pathfinding;

int main(int argc, char** argv) {
    // TODO: Make the function call more abstract for
    // the end user
    // Number of rows in the grid
    uint32_t rows{40};

    // Number of cols in the grid
    uint32_t cols{40};

    // Size of individual cell in pixels
    uint32_t cell_size{20};

    // Choose a starting point
    PF::Cell start(15, 12);

    // Choose an ending point
    PF::Cell end(39, 39);

    // Create a grid PathFinder Object
    PF::PathFinder* grid_path_finder = new PF::PathFinder(
        PF::EnvironmentType::GRID, PF::PathFindingMethod::BFS,
        PF::ObstacleGenerationMethod::FISHER_YATES_SHUFFLE,
        /**num_obstacles**/ 300, rows, cols, cell_size, start, end);

    // Create a visualizer object for the grid object
    PF::Visualizer* grid_visualizer(new PF::Visualizer(grid_path_finder));
    // Set title
    grid_visualizer->setTitle("GRID");
    // Set theme
    grid_visualizer->setTheme(PF::Theme::LIGHT);
    // Initiate the grid
    grid_visualizer->init();
    // Show
    grid_visualizer->show();

    // Create a maze PathFinder Object
    PF::PathFinder* maze_path_finder = new PF::PathFinder(
        PF::EnvironmentType::MAZE, PF::PathFindingMethod::BFS,
        PF::MazeGenerationMethod::RANDOMIZED_DFS, rows, cols, cell_size, start,
        end);

    // Create a visualizer object for the maze object
    PF::Visualizer* maze_visualizer(new PF::Visualizer(maze_path_finder));
    // Set title
    maze_visualizer->setTitle("MAZE");
    // Set theme
    maze_visualizer->setTheme(PF::Theme::LIGHT);
    // Initiate the grid
    maze_visualizer->init();
    // Show
    maze_visualizer->show();

    return 0;
}