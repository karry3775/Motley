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
    PF::Cell start(0, 0);

    // Choose an ending point
    PF::Cell end(39, 39);

    // Create the PathFinderObject
    PF::PathFinder* path_finder =
        new PF::PathFinder(PF::EnvironmentType::MAZE, PF::Method::BFS,
                           PF::GenerationMethod::RANDOMIZED_DFS, rows, cols,
                           cell_size, start, end);

    /** Visualize the environment **/
    // Create a visualizer object for the grid object
    PF::Visualizer* visualizer(new PF::Visualizer(path_finder));
    // Set title
    visualizer->setTitle("MAZE");
    // Set theme
    visualizer->setTheme(PF::Theme::LIGHT);
    // Initiate the grid
    visualizer->init();
    // Show
    visualizer->show();

    return 0;
}