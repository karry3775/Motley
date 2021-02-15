#pragma once

#include "Cell.h"

namespace pathfinding {
class Corner : public Cell {
   public:
    Corner(const uint32_t& row, const uint32_t& col) : Cell(row, col) {}
};
}  // namespace pathfinding