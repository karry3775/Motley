#include <PathFinding.h>
#include <glog/logging.h>

namespace PF = pathfinding;

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    // Number of rows and columns in the environment
    uint32_t n_rows{30}, n_cols{40};
    // Cell size in the environment
    uint32_t cell_size{20};
    // Start and end points
    PF::Cell start(1, 1), end(20, 20);

    // Create a Pathfinder object
    std::unique_ptr<PF::PathFinder> grid_path_finder(new PF::PathFinder(
        PF::EnvironmentType::GRID, PF::PathFindingMethod::BFS,
        PF::ObstacleGenerationMethod::FISHER_YATES_SHUFFLE, 0.1, n_rows, n_cols,
        cell_size, start, end, true));

    // Show final path
    grid_path_finder->showFinalPath();

    // Get the raw path having cell constructor
    // this might prohibit portability, as people might have
    // to manually convert it to vector paths
    // Could be useful for developers who want to use the cell kind
    // of structs
    const auto path = grid_path_finder->getPath();

    // Print out the path
    std::cout << "Final Path\n";
    for (auto& waypoint : path) {
        std::cout << *waypoint << "\n";
    }
    std::cout << "\n";

    // For decoupled developed, there is also an option to get a simple path out
    const auto simple_path = grid_path_finder->getSimplePath();

    // Print the simple path
    std::cout << "Simple path\n";
    for (auto& wp_pair : simple_path) {
        std::cout << wp_pair.first << ", " << wp_pair.second << "\n";
    }
    std::cout << "\n";

    return 0;
}