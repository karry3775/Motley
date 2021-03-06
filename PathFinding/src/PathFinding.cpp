#include "PathFinding.h"
#include "PathFindingUtils.h"
#include <opencv2/opencv.hpp>

namespace pathfinding {

PathFinder::PathFinder(const EnvironmentType& env_type,
                       const PathFindingMethod& pf_method,
                       const ObstacleGenerationMethod& obs_gen_method,
                       const double& obstacle_perc, const uint32_t& rows,
                       const uint32_t& cols, const uint32_t& cell_size,
                       const Cell& start, const Cell& end,
                       bool show_path_progression)
    : start_{start},
      end_{end},
      pf_method_{pf_method},
      env_type_{env_type},
      show_path_progression_{show_path_progression} {
    CHECK(env_type_ == EnvironmentType::GRID) << "Expected a GRID type!";

    // Assign a seed
    srand(time(NULL));

    env_ = new Grid(rows, cols, cell_size, obs_gen_method, obstacle_perc);

    // Assign obstacles
    obstacles_ = env_->getObstacles();

    // Check if start and end points are blocked
    LOG_IF(FATAL, isCellBlocked(start_)) << "Start cell is blocked!";
    LOG_IF(FATAL, isCellBlocked(end_)) << "End cell is blocked!";

    // Find path using the suggested method above
    path_found_ = findPath();

    // Create the visualizer object when everything is set
    visualizer = std::make_unique<Visualizer>(this);

    // Set up visualizer
    setUpVisualizer();

    // Show path progression
    if (show_path_progression_) {
        visualizer->showPathProgression(explored_path_);
    }
}

PathFinder::PathFinder(const EnvironmentType& env_type,
                       const PathFindingMethod& pf_method,
                       const MazeGenerationMethod& maze_gen_method,
                       const uint32_t& rows, const uint32_t& cols,
                       const uint32_t& cell_size, const Cell& start,
                       const Cell& end, bool show_path_progression)
    : start_{start},
      end_{end},
      pf_method_{pf_method},
      env_type_{env_type},
      show_path_progression_{show_path_progression} {
    CHECK(env_type_ == EnvironmentType::MAZE) << "Expected a MAZE type!";

    // Assign a seed
    srand(time(NULL));

    env_ = new Maze(rows, cols, cell_size, maze_gen_method);

    // Find path using the suggested method above
    path_found_ = findPath();

    // Create the visualizer object when everything is set
    visualizer = std::make_unique<Visualizer>(this);

    // Set up visualizer
    setUpVisualizer();

    // Show path progression
    if (show_path_progression_) {
        visualizer->showPathProgression(explored_path_);
    }
}

PathFinder::PathFinder(const EnvironmentType& env_type,
                       const PathFindingMethod& pf_method,
                       const char* env_image_path, const uint32_t& cell_size,
                       const Cell& start, const Cell& end,
                       bool show_path_progression)
    : start_{start},
      end_{end},
      pf_method_{pf_method},
      env_type_{env_type},
      show_path_progression_{show_path_progression} {
    CHECK(env_type_ == EnvironmentType::GRID) << "Expected a GRID type!";

    // Assign a seed
    srand(time(NULL));

    setGridFromImage(env_image_path, cell_size);

    // Check if start and end points are blocked
    LOG_IF(FATAL, isCellBlocked(start_)) << "Start cell is blocked!";
    LOG_IF(FATAL, isCellBlocked(end_)) << "End cell is blocked!";

    // Find path using the suggested method above
    path_found_ = findPath();

    // Create the visualizer object when everything is set
    visualizer = std::make_unique<Visualizer>(this);

    // Set up visualizer
    setUpVisualizer();

    // Show path progression
    if (show_path_progression_) {
        visualizer->showPathProgression(explored_path_);
    }
}

const Environment<Cell>* PathFinder::getEnvironment() const { return env_; }

const EnvironmentType& PathFinder::getEnvironmentType() const {
    return env_type_;
}

const Path<Cell*> PathFinder::getPath() const { return path_; }

const SimplePath<uint32_t> PathFinder::getSimplePath() const {
    SimplePath<uint32_t> simple_path;

    if (path_.empty()) return simple_path;

    for (auto& cell : path_) {
        simple_path.emplace_back(
            std::make_pair(cell->getRow(), cell->getCol()));
    }

    return simple_path;
}

const Cell PathFinder::getStartCell() const { return start_; }

const Cell PathFinder::getEndCell() const { return end_; }

const std::vector<std::vector<int>> PathFinder::getObstacles() const {
    return obstacles_;
}

bool PathFinder::doesPathExists() const { return path_found_; }

void PathFinder::showFinalPath() {
    if (show_path_progression_) {
        // The first instance of visualizer object must have been
        // deinitialized
        // As such we need to explicitly initialize it here
        setUpVisualizer();
    }
    visualizer->showFinalPath();
}

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

// pseudo code soruce [NOT USING THIS]  :
// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm [USING THIS]
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
bool PathFinder::findPathDijkstra() {
    DistanceMap<Cell*> dist;
    PredecessorMap<Cell*> pred;

    // Min heap to extract vertex with min distance
    MinHeap<int, Cell*> min_heap;

    // Get the adj_ list
    const auto adj = env_->getAdjacencyList();

    for (auto itr = adj.begin(); itr != adj.end(); ++itr) {
        // Mark the dist to be infinite
        dist[itr->first] = INT_MAX;
        // Mark the predecessor to be self
        pred[itr->first] = itr->first;
    }

    // Setup data for source/start point
    dist[env_->at(start_)] = 0;
    min_heap.push(std::make_pair(0, env_->at(start_)));

    bool path_found;

    while (!min_heap.empty()) {
        // Step 1: Get the vertex with minimum distance value
        auto current = min_heap.top().second;
        // Step 2: Erase that vertex from the unvisited set
        min_heap.pop();

        // Add current to explored
        explored_path_.emplace_back(current);

        // Step 3: For each neighbour that vertex check if a
        // shorted circuit could be formed
        for (size_t i = 0; i < adj.at(current).size(); ++i) {
            const auto neighbour = adj.at(current)[i];

            if (dist[current] + 1 < dist[neighbour]) {
                // TODO: Make the cost between neighbours to be a variable later
                dist[neighbour] = dist[current] + 1;
                pred[neighbour] = current;
                min_heap.push(std::make_pair(dist[neighbour], neighbour));
            }

            // Check if end point is reached
            if (neighbour == env_->at(end_)) {
                path_found = true;
                break;
            }
        }
    }

    // Form the path using predecessor
    getPathFromPredecessorMap(pred);

    return path_found;
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

        // Add current to explored
        explored_path_.emplace_back(current);

        // visit its neighbours one by one
        for (int i = 0; i < adj[current].size(); ++i) {
            if (visited.find(adj[current][i]) == visited.end()) {
                // mark it as visited
                visited.insert(adj[current][i]);
                // update the distance to be one more than current
                // TODO: Make the cost between neighbours to be a variable later
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
    getPathFromPredecessorMap(pred);

    return path_found;
}

void PathFinder::getPathFromPredecessorMap(const PredecessorMap<Cell*>& pred) {
    auto current = env_->at(end_);
    while (pred.at(current) != current) {
        path_.push_back(current);
        current = pred.at(current);
    }

    // Insert the start point
    path_.push_back(env_->at(start_));

    // Reverse the path
    std::reverse(path_.begin(), path_.end());
}

void PathFinder::setUpVisualizer() {
    // Set visualizer attributes based on environment type
    const char* title;
    Theme theme;
    switch (env_type_) {
        case EnvironmentType::GRID:
            title = "GRID";
            theme = Theme::LIGHT;
            break;
        case EnvironmentType::MAZE:
            title = "MAZE";
            theme = Theme::LIGHT;
            break;
        default:
            LOG(FATAL) << "Unknown environment type!";
    }

    // Set title
    visualizer->setTitle(title);
    // Set theme
    visualizer->setTheme(theme);
    // Initiate the visualizer
    visualizer->init();
}

bool PathFinder::isCellBlocked(const Cell& cell) const {
    if (obstacles_.size() > cell.getRow() &&
        obstacles_[0].size() > cell.getCol()) {
        return obstacles_[cell.getRow()][cell.getCol()] == 1;
    }

    return false;
}

void PathFinder::setGridFromImage(const char* image_path,
                                  const uint32_t& cell_size) {
    // First check if the file path exists
    CHECK_GE(access(image_path, R_OK), 0) << "Image path does not exists!";

    // Open image as a matrix whose pixel values can be read
    // Major GOTCHA! -- Not specifying the image type as CV_8UC1
    // and later not properly accesing it
    cv::Mat image = cv::imread(image_path, CV_8UC1);

    const uint32_t rows = image.rows / cell_size;
    const uint32_t cols = image.cols / cell_size;

    // Resize obstacles
    obstacles_.resize(rows, std::vector<int>(cols, 0));

    std::vector<std::pair<int, int>> available_cells;
    // Access the image with step size of cell size
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (image.at<uchar>(row * cell_size, col * cell_size) == 0) {
                obstacles_[row][col] = 1;
            } else {
                available_cells.emplace_back(std::make_pair(row, col));
            }
        }
    }

    if (isCellBlocked(start_) || isCellBlocked(end_)) {
        CHECK_GE(available_cells.size(), 2)
            << "Found blocked cells! Not enough available cells to auto assign "
               "them!";

        std::cerr << "Found blocked cells (start or end), Choosing from "
                     "available cells at random\n";

        // Extract random index for the start point
        int rand_index = rand() % available_cells.size();
        // Set start_
        start_ = Cell(available_cells[rand_index].first,
                      available_cells[rand_index].second);

        // Remove the start index
        available_cells.erase(available_cells.begin() + rand_index);

        // Extract random index for the end point
        rand_index = rand() % available_cells.size();
        // Set end
        end_ = Cell(available_cells[rand_index].first,
                    available_cells[rand_index].second);
    }

    env_ = new Grid(rows, cols, cell_size, obstacles_);
}

}  // namespace pathfinding