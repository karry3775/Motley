#include <AntColonySimulation.h>

namespace AC = ant_colony;

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);

    // Step 1: Create an AntColonySim object
    std::unique_ptr<AC::AntColonySim> ant_colony_sim(new AC::AntColonySim(20));

    // Step 2: Show the AntColonySim
    ant_colony_sim->show();

    return 0;
}
