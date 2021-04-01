#include <Boids.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);

    std::unique_ptr<boids::Boids> boids_obj(new boids::Boids(150));

    boids_obj->show();
    return 0;
}