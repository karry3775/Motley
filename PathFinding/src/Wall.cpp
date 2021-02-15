#include "Wall.h"

namespace pathfinding {

Wall::Wall(const Cell& c1, const Cell& c2) {
    // Check for item size less than two
    // TODO: Test this
    CHECK(items_.size() <= 2) << "More than two items not possible";

    items_.insert(c1);
    items_.insert(c2);
}

}  // namespace pathfinding