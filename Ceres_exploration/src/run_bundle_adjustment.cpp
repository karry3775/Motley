#include "bundle_adjustment.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    bundle_adjustment::solve();

    return 0;
}