#include <hello_world.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    hello_world::solve();

    return 0;
}
