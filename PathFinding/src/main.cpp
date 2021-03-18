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

    std::unique_ptr<PF::PathFinder> grid_path_finder(new PF::PathFinder(
        PF::EnvironmentType::GRID, PF::PathFindingMethod::DIJKSTRA,
        PF::ObstacleGenerationMethod::FISHER_YATES_SHUFFLE,
        /**num obstacles**/ 300, rows, cols, cell_size, start, end));

    // Create a visualizer object for the grid object
    std::unique_ptr<PF::Visualizer> grid_visualizer(
        new PF::Visualizer(grid_path_finder.get()));
    // Set title
    grid_visualizer->setTitle("GRID");
    // Set theme
    grid_visualizer->setTheme(PF::Theme::LIGHT);
    // Initiate the grid
    grid_visualizer->init();
    // Show
    grid_visualizer->show();

    // Create a maze PathFinder Object
    std::unique_ptr<PF::PathFinder> maze_path_finder(new PF::PathFinder(
        PF::EnvironmentType::MAZE, PF::PathFindingMethod::DIJKSTRA,
        PF::MazeGenerationMethod::RANDOMIZED_DFS, rows, cols, cell_size, start,
        end));

    // Create a visualizer object for the maze object
    std::unique_ptr<PF::Visualizer> maze_visualizer(
        new PF::Visualizer(maze_path_finder.get()));
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