#pragma once

#include "Cell.h"

#include "EnvironmentGeneration.h"

namespace pathfinding {
class Grid : public Environment<Cell> {
   public:
    Grid();
    Grid(uint32_t rows, uint32_t cols);
    const uint32_t getRows() const;
    const uint32_t getCols() const;

   private:
    uint32_t rows_;
    uint32_t cols_;
};

}  // namespace pathfinding