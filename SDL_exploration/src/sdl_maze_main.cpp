#include "sdl_maze.h"
#include <iostream>

int main() {
    std::cout << "Hello" << std::endl;

    // temp : Lets create a MazeGenerator object
    // and try to design our visualizer
    maze::MazeGenerator maze_generator;

    // maze_generator.generateMaze(); // TOOD: fix it its currently running
    // infinitely

    if (!maze_generator.showMaze()) {
        // detailed error message is already handled
        // by showMaze
        std::cout << "Failed to display maze! Aborting!" << std::endl;
    }
    return 0;
}