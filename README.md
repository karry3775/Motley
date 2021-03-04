# Motley
This repository is made for the sole purpose of doing random assortment of projects that might not be cohesive. This is intended to take away any commitment issues and just take joy in the process of coding. The projects / codes found in this repositories can range from just simple studies of existing projects spread across the internet to full applications developed from scratch. 

# Maze generation

## Randomized depth search (Rendered using SDL)
![maze](SDL_exploration/images/mazegen.gif)

## Path finding tool
![grid_bfs](PathFinding/images/grid_bfs.gif)
![maze_bfs](PathFinding/images/maze_2_bfs.gif)

### Sample usage
```cpp
#include "Visualization.h"
#include "PathFinding.h"

namespace PF = pathfinding;

int main(int argc, char** argv) {
    // Define basic parameters defining the path finder
    uint32_t rows{40}, cols{40}, cell_size{20};
    PF::Cell start(15, 12), end(39, 39);


    /********************* PATH FINDING IN GRID BASED ENVIRONMENT *******************/
    // Finding a path in grid environment
    PF::PathFinder* grid_path_finder = new PF::PathFinder(
        PF::EnvironmentType::GRID,  /** Specifying GRID type environment **/
        PF::PathFindingMethod::BFS, /** Method to be used for path finding **/
        PF::ObstacleGenerationMethod::FISHER_YATES_SHUFFLE, /** Method to be used for generation of random obstacles **/
        300, /** Number of obstacles to be generated **/
        rows, /** Number of rows **/
        cols, /** Number of cols **/
        cell_size, /** Size of the square cells in pixels **/
        start, /** Starting cell for the path **/
        end, /** Ending cell for the path **/
    );

    // Visualize the path in grid environment
    PF::Visualizer* grid_visualizer(new PF::Visualizer(grid_path_finder));
    // Set title
    grid_visualizer->setTitle("GRID");
    // Set theme
    grid_visualizer->setTheme(PF::Theme::LIGHT);
    // Initia the grid
    grid_visualizer->init();
    // Show
    grid_visualizer->show();

    /********************* PATH FINDING IN MAZE ENVIRONMENT *************************/
    PF::PathFinder* maze_path_finder =  new PF::PathFinder(
        PF::EnvironmentType::MAZE, /** Specify MAZE environment **/
        PF::PathFindingMethod::BFS, /** Method to be used for path finding **/
        PF::MazeGenerationMethod::RANDOMIZED_DFS, /** Method to be used for maze generation **/
        rows, /** Number of rows **/
        cols, /** Number of cols **/
        cell_size, /** Size of square cells in pixels **/
        start, /** Starting cell for the path **/
        end, /** Ending cell for the path **/
    );

    // Visualize the path in maze environment
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
```


