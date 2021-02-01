#include "PathFinding.h"
#include "PathFindingUtils.h"

namespace pathfinding {

PathFinder::PathFinder(uint32_t rows, uint32_t cols, Cell start, Cell end,
                       PathFinder::Method method)
    : start_{start}, end_{end}, method_{method} {
    // Generate a grid environment
    grid_ = new Grid(rows, cols);

    // Find path using the suggested method above
    findPath();
}

void PathFinder::findPath() {
    switch (method_) {
        case DIJKSTRA:
            findPathDijkstra();
            break;
        case ASTAR:
            findPathAstar();
            break;
        case SAMPLE:
            findPathSample();
            break;
        case HIERARCHICAL:
            findPathHierarchical();
            break;
        case BFS:
            findPathBfs();
            break;
        case DFS:
            findPathDfs();
            break;
        default:
            break;
    }
}

void PathFinder::findPathDijkstra() {
    // TODO
}

void PathFinder::findPathAstar() {
    // TODO
}

void PathFinder::findPathSample() {
    // TODO
}

void PathFinder::findPathHierarchical() {
    // TODO
}

void PathFinder::findPathBfs() {
    // TODO
}

void PathFinder::findPathDfs() {
    // TODO
}

}  // namespace pathfinding