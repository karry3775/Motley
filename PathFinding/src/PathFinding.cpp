#include "PathFinding.h"
#include "PathFindingUtils.h"

namespace pathfinding {

PathFinder::PathFinder(const uint32_t& rows, const uint32_t& cols,
                       const uint32_t& cell_size, const Cell& start,
                       const Cell& end, const Method& method,
                       const EnvironmentType& env_type)
    : start_{start}, end_{end}, method_{method}, env_type_{env_type} {
    // Generate a grid environment
    grid_ = new Grid(rows, cols, cell_size);

    // Find path using the suggested method above
    findPath();
}

const Grid* PathFinder::getGrid() const { return grid_; }

const Path<Cell*> PathFinder::getPath() const { return path_; }

void PathFinder::findPath() {
    switch (method_) {
        case Method::DIJKSTRA:
            findPathDijkstra();
            break;
        case Method::ASTAR:
            findPathAstar();
            break;
        case Method::SAMPLE:
            findPathSample();
            break;
        case Method::HIERARCHICAL:
            findPathHierarchical();
            break;
        case Method::BFS:
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
    std::queue<Cell*> cell_queue;

    // A set to keep track of what's
    // already been visited
    std::set<Cell*> visited;

    PredecessorMap<Cell*> pred;
    DistanceMap<Cell*> dist;
    // Set the distances to be INF
    // and predecessor to be itself as no parents exists yet
    auto adj = grid_->getAdjacencyList();
    for (auto itr = adj.begin(); itr != adj.end(); ++itr) {
        dist[itr->first] = INT_MAX;
        pred[itr->first] = itr->first;
    }

    // We will start by visiting the starting point
    // thus marking it visited and setting the distance
    // to be 0 and pushing it into the queue
    visited.insert(grid_->at(start_));
    // or may be just ask the user to specify the row and column instead.
    dist[grid_->at(start_)] = 0;
    cell_queue.push(grid_->at(start_));

    // standard BFS algorithm
    while (!cell_queue.empty()) {
        Cell* current = cell_queue.front();
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
                if (adj[current][i] == grid_->at(end_)) {
                    break;
                }
            }
        }
    }

    // Form the path using predecessor
    auto current = grid_->at(end_);
    while (pred[current] != current) {
        path_.push_back(current);
        current = pred[current];
    }

    // Additionally push back the starting point
    path_.push_back(grid_->at(start_));

    // Reverse the path
    std::reverse(path_.begin(), path_.end());
}

}  // namespace pathfinding