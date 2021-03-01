#include "core.h"

int main(int argc, char** argv) {
    LOG_IF(FATAL, argc != 2) << "File path not specified!";

    FILE* fptr = fopen(argv[1], "r");
    if (fptr == NULL) return false;

    int val;
    int num_scanned = fscanf(fptr, "%d", &val);

    CHECK(num_scanned != 0) << "Unable to get data from file!";

    LOG(INFO) << "val is: " << val;

    return 0;
}