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

    /**
     * Gets the pointer to the cell in the grid based on
     * information provided by the Cell object
     * @param Cell Cell describing the location to be accessed
     * @return Cell pointer for the grid
     */
    virtual Cell* at(const Cell&) override;

    /**
     * Gets the pointer to the cell in the grid based on
     * row and column information
     * @param row row for the cell
     * @param col col for the cell
     * @return Cell pointer for the grid at given row and col
     */
    virtual Cell* at(const uint32_t& row, const uint32_t& col) override;

    /**
     * Helper function to populate obstacles in the environment
     * @param row row for the obstacle
     * @param col col for the obstacle
     */
    virtual void pushObstacles(const uint32_t& row,
                               const uint32_t& col) override;

    /**
     * Getter for obstacles
     * @return 2D matrix resprenting obstacle map
     */
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