#include "PathFinding.h"
#include "PathFindingUtils.h"

namespace pathfinding {

PathFinder::PathFinder(uint32_t rows, uint32_t cols, uint32_t cell_size,
                       Cell start, Cell end, PathFinder::Method method)
    : start_{start}, end_{end}, method_{method} {
    // Generate a grid environment
    grid_ = new Grid(rows, cols, cell_size);

    // Find path using the suggested method above
    findPath();
}

const Grid* PathFinder::getGrid() const {
    return grid_;
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
    // A queue to facilitate list of vertices/Cells
    // to be traversed in BFS
    std::queue<Cell> cell_queue;

    // A set to keep track of what's
    // already been visited
    std::set<Cell> visited;

    // Set the distances to be INF
    // and predecessor to be itself as no parents exists yet
    PredecessorMap<Cell> pred;
    DistanceMap<Cell> dist;
    auto adj = grid_->getAdjacencyList();
    for (auto itr = adj.begin(); itr != adj.end(); ++itr) {
        visited.insert(itr->first);
        dist[itr->first] = INT_MAX;
        pred[itr->first] = itr->first;
    }

    // We will start by visiting the starting point
    // thus marking it visited and setting the distance
    // to be 0 and pushing it into the queue
    visited.insert(start_);
    dist[start_] = 0;
    cell_queue.push(start_);

    // standard BFS algorithm
    while (!cell_queue.empty()) {
        Cell current = cell_queue.front();
        cell_queue.pop();

        // visit its neighbours one by one
        for (int i = 0; i < adj[current].size(); ++i) {
            if (visited.find(adj[current][i]) == visited.end()) {
                // mark it as visited
                visited.insert(adj[current][i]);
                // update the distance to be one more than current
                dist[adj[current][i]] = 1 + dist[current];
                // make current as the predecessor
                pred[adj[current][i]] = current;
                // push it in the queue to be processed later
                cell_queue.push(adj[current][i]);

                // We can stop the BFS when we find the destination
                if (adj[current][i] == end_) {
                    break;
                }
            }
        }
    }

    // TODO: Form path using pred
}

}  // namespace pathfinding