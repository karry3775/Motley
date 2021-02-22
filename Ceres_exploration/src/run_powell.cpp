#include <powell_function.h>

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    powell::solve();

    return 0;
}
