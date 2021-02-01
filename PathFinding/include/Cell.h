#pragma once

#include "Core.h"

namespace pathfinding {
class Cell {
   public:
    Cell(uint32_t x, uint32_t y) : x_{x}, y_{y} {};

    // Compare operator for Cell
    // Essential for this be considered as a key in
    // any map data structure
    bool operator<(const Cell& c) const {
        return (this->x_ <= c.x_ && this->y_ <= c.y_);
    }

    bool operator==(const Cell& c) const {
        return (this->x_ == c.x_ && this->y_ == c.y_);
    }

   private:
    uint32_t x_;
    uint32_t y_;
};

}  // namespace pathfinding