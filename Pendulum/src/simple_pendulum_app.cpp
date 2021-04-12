#include <simple_pendulum.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::unique_ptr<pendulum::SimplePendulum> simple_pendulum =
        std::make_unique<pendulum::SimplePendulum>(10, 3, 0);

    simple_pendulum->show();

    return 0;
}