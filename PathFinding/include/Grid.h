#pragma once

#include "Cell.h"

#include "EnvironmentGeneration.h"

namespace pathfinding {

enum class ObstacleGenerationMethod { MANUAL, FISHER_YATES_SHUFFLE };

class Grid : public Environment<Cell> {
   public:
    Grid();
    Grid(const uint32_t& rows, const uint32_t& cols, const uint32_t& cell_size,
         const ObstacleGenerationMethod& obs_gen_method,
         const uint32_t& num_obstacles);

    virtual const uint32_t getRows() const override;
    virtual const uint32_t getCols() const override;
    virtual const uint32_t getCellSize() const override;

    // Getters for easy element access
    virtual Cell* at(const Cell&) override;
    virtual Cell* at(const uint32_t& row, const uint32_t& col) override;

    // public function to assign obstacles
    virtual void pushObstacles(const uint32_t& row,
                               const uint32_t& col) override;

    // Getter for obstacles
    virtual std::vector<std::vector<int>> getObstacles() const override;

   private:
    // TODO: Rename to something better (Make this as generate so that
    // it is consistent with the Maze)
    void create();
    void generateObstacles();
    uint32_t rows_;
    uint32_t cols_;
    uint32_t cell_size_;
    ObstacleGenerationMethod obs_gen_method_;
    uint32_t num_obstacles_;

    std::vector<std::vector<Cell*>> matrix_;
    std::vector<std::vector<int>> obstacles_;
};

}  // namespace pathfinding