#pragma once

#include "Cell.h"

#include "EnvironmentGeneration.h"

namespace pathfinding {
class Grid : public Environment<Cell> {
   public:
    Grid();
    Grid(uint32_t rows, uint32_t cols, uint32_t cell_size);
    const uint32_t getRows() const;
    const uint32_t getCols() const;
    const uint32_t getCellSize() const;

   private:
    // TODO: Rename to something better
    void create();
    uint32_t rows_;
    uint32_t cols_;
    uint32_t cell_size_;
    std::vector<std::vector<Cell*>> grid_;
};

}  // namespace pathfinding