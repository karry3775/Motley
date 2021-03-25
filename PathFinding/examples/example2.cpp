#include <PathFinding.h>
#include <glog/logging.h>

namespace PF = pathfinding;

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    // Start and end points
    PF::Cell start(0, 0), end(49, 49);  // TODO: Need to provide the user with
    // a list of available start points and end points in general
    // as they would not know which states are free
    const uint32_t cell_size{20};

    // TODO: Make this a argument
    const char* env_image_path =
        "/home/kartik/Documents/Motley_data/environment_images/env2.png";

    // Create a Pathfinder object
    std::unique_ptr<PF::PathFinder> grid_path_finder(new PF::PathFinder(
        PF::EnvironmentType::GRID, PF::PathFindingMethod::BFS, env_image_path,
        cell_size, start, end, true));

    // TODO: Pick up from here tomorrow

    return 0;
}