#include <Tiling.h>
#include <iostream>

int main() {
    tiling::Tiler tiler(5, 150);

    tiling::TilingSequences all_ts;

    tiler.getAllTilings(all_ts);

    std::cerr << "Found " << all_ts.size() << " sequences!\n";

    tiler.visualize(all_ts);

    return 0;
}