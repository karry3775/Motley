#include "sdl_maze.h"
#include <iostream>

int main() {
    std::cout << "Hello" << std::endl;

    maze::MazeGenerator maze_generator;

    maze_generator.generateMaze();

    // maze_generator.displayMazeCells();

    if (!maze_generator.showMaze()) {
        // detailed error message is already handled
        // by showMaze
        std::cout << "Failed to display maze! Aborting!" << std::endl;
    } else {
        std::cout << "Finished cleanly!" << std::endl;
    }
    return 0;
}