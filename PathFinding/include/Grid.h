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

    // Getters for easy element access
    Cell* at(const Cell&);
    Cell* at(const uint32_t& row, const uint32_t& col);

   private:
    // TODO: Rename to something better (Make this as generate so that
    // it is consistent with the Maze)
    void create();
    uint32_t rows_;
    uint32_t cols_;
    uint32_t cell_size_;
    std::vector<std::vector<Cell*>> matrix_;
};

}  // namespace pathfinding