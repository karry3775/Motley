#include "PathFinding.h"
#include "PathFindingUtils.h"
#include <queue>

namespace pathfinding {

PathFinder::PathFinder(const EnvironmentType& env_type,
                       const PathFindingMethod& pf_method,
                       const ObstacleGenerationMethod& obs_gen_method,
                       const uint32_t& num_obstacles, const uint32_t& rows,
                       const uint32_t& cols, const uint32_t& cell_size,
                       const Cell& start, const Cell& end)
    : start_{start}, end_{end}, pf_method_{pf_method}, env_type_{env_type} {
    CHECK(env_type_ == EnvironmentType::GRID) << "Expected a GRID type!";

    env_ = new Grid(rows, cols, cell_size, obs_gen_method, num_obstacles);

    // Assign obstacles
    obstacles_ = env_->getObstacles();

    // Find path using the suggested method above
    path_found_ = findPath();

    // Assign a seed
    srand(12345);
}

PathFinder::PathFinder(const EnvironmentType& env_type,
                       const PathFindingMethod& pf_method,
                       const MazeGenerationMethod& maze_gen_method,
                       const uint32_t& rows, const uint32_t& cols,
                       const uint32_t& cell_size, const Cell& start,
                       const Cell& end)
    : start_{start}, end_{end}, pf_method_{pf_method}, env_type_{env_type} {
    CHECK(env_type_ == EnvironmentType::MAZE) << "Expected a MAZE type!";

    env_ = new Maze(rows, cols, cell_size, maze_gen_method);

    // Find path using the suggested method above
    path_found_ = findPath();

    // Assign a seed
    srand(12345);
}

const Environment<Cell>* PathFinder::getEnvironment() const { return env_; }

const EnvironmentType& PathFinder::getEnvironmentType() const {
    return env_type_;
}

const Path<Cell*> PathFinder::getPath() const { return path_; }

const std::vector<std::vector<int>> PathFinder::getObstacles() const {
    return obstacles_;
}

bool PathFinder::doesPathExists() const { return path_found_; }

bool PathFinder::findPath() {
    switch (pf_method_) {
        case PathFindingMethod::DIJKSTRA:
            return findPathDijkstra();
            break;
        case PathFindingMethod::ASTAR:
            return findPathAstar();
            break;
        case PathFindingMethod::SAMPLE:
            return findPathSample();
            break;
        case PathFindingMethod::HIERARCHICAL:
            return findPathHierarchical();
            break;
        case PathFindingMethod::BFS:
            return findPathBfs();
            break;
        default:
            break;
    }

    return false;
}

// pseudo code form  : https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
bool PathFinder::findPathDijkstra() {
    // Step 1: Mark all node as unvisited
    std::set<Cell*> unvisited{};
    DistanceMap<Cell*> dist;
    PredecessorMap<Cell*> pred;
    // Priority queue (Min heap fashion to aid in finding the vertex with
    // minimum cost)
    std::priority_queue<Cell*, std::vector<Cell*>, std::greater<Cell*>> pq;

    // Get the adj_ list
    const auto adj = env_->getAdjacencyList();

    for (auto itr = adj.begin(); itr != adj.end(); ++itr) {
        unvisited.insert(itr->first);
        // Mark the dist to be infinite
        dist[itr->first] = INT_MAX;
        // Mark the predecessor to be self
        pred[itr->first] = itr->first;
        // Insert it into the priority queue
        pq.emplace(itr->first);
    }

    // Step 2: Assign the start_node a distance value of 0
    dist[env_->at(start_)] = 0;

    while (!unvisited.empty()) {
        // Step 1: Get the vertex with minimum distance value

        // Step 2: Erase that vertex from the unvisited set

        // Step 3: For each neighbour that vertex check if a
        // shorted circuit could be formed
    }

    return true;
}

bool PathFinder::findPathAstar() {
    // TODO
    return false;
}

bool PathFinder::findPathSample() {
    // TODO
    return false;
}

bool PathFinder::findPathHierarchical() {
    // TODO
    return false;
}

bool PathFinder::findPathBfs() {
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
    auto adj = env_->getAdjacencyList();
    for (auto itr = adj.begin(); itr != adj.end(); ++itr) {
        dist[itr->first] = INT_MAX;
        pred[itr->first] = itr->first;
    }

    // We will start by visiting the starting point
    // thus marking it visited and setting the distance
    // to be 0 and pushing it into the queue
    visited.insert(env_->at(start_));
    // or may be just ask the user to specify the row and column instead.
    dist[env_->at(start_)] = 0;
    cell_queue.push(env_->at(start_));

    bool path_found = false;
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
                if (adj[current][i] == env_->at(end_)) {
                    path_found = true;
                    break;
                }
            }
        }
    }

    // Form the path using predecessor
    auto current = env_->at(end_);
    while (pred[current] != current) {
        path_.push_back(current);
        current = pred[current];
    }

    // Additionally push back the starting point
    path_.push_back(env_->at(start_));

    // Reverse the path
    std::reverse(path_.begin(), path_.end());

    return path_found;
}

}  // namespace pathfinding