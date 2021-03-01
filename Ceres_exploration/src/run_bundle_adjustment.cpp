#include "bundle_adjustment.h"

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);

    if (argc != 2) {
        LOG(FATAL) << "No bal problem file path specified!";
        return 1;
    }

    bundle_adjustment::solve(argv);

    return 0;
}