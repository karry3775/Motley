#include "PathFinding.h"

int main(int argc, char** argv) {
    // Create the PathFinderObject
    pathfinding::PathFinder* path_finder =
        new pathfinding::PathFinder(pathfinding::PathFinder::DIJKSTRA);
    return 0;
}