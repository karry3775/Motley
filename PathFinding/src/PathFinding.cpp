#include "PathFinding.h"

namespace pathfinding {

PathFinder::PathFinder(PathFinder::Method method) : method_{method} {
    findPath(method);
}

void PathFinder::findPath(PathFinder::Method method) {
    switch (method) {
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

}  // namespace pathfinding