#include "PathFinding.h"

namespace PF = pathfinding;

int main(int argc, char** argv) {
    // TODO: Make the function call more abstract for
    // the end user
    // Number of rows in the grid
    uint32_t rows{10};

    // Number of cols in the grid
    uint32_t cols{10};

    // Choose a starting point
    PF::Cell start(0, 0);

    // Choose an ending point
    PF::Cell end(0, 0);

    // Create the PathFinderObject
    PF::PathFinder* path_finder =
        new PF::PathFinder(rows, cols, start, end, PF::PathFinder::BFS);
    return 0;
}