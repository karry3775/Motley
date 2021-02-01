#include "PathFinding.h"
#include "Grid.h"
#include <iostream>

int main(int argc, char** argv) {
    // Create the grid object
    pathfinding::Grid* grid = new pathfinding::Grid(static_cast<uint32_t>(10),
                                                    static_cast<uint32_t>(10));

    std::cout << grid->getSize() << std::endl;

    return 0;
}