#pragma once

#include "Core.h"

#include "Corner.h"

namespace pathfinding {

class Wall {
   public:
    Wall(const Corner&, const Corner&);
    ~Wall();

   private:
    // To store the wall items (i.e. the two Cells, forming
    // the walls)
    std::set<Corner> items_;
};

}  // namespace pathfinding