#pragma once

#include "Core.h"

#include "Cell.h"

namespace pathfinding {

class Wall {
   public:
    Wall(const Cell&, const Cell&);
    ~Wall();

   private:
    // To store the wall items (i.e. the two Cells, forming
    // the walls)
    std::set<Cell> items_;
};

}  // namespace pathfinding