#pragma once

#include "sdl_maze_core.h"
#include "sdl_maze_utils.h"

namespace maze {

class MazeGenerator {
   public:
    /**
     * Default constructor for the class
     */
    MazeGenerator();
    /**
     * Constructor to initiate the Maze
     */
    MazeGenerator(uint32_t rows, uint32_t cols, uint32_t cell_size);

   private:
    /**
     * Randomized depth first search maze generation method
     */
    void randomizedDepthFirstSearch();
    /**
     *  Helper function for the above method
     */
    void randomizedDepthFirstSearchHelper(
        uint32_t row, uint32_t col, std::set<std::pair<int, int>> visited);

    std::vector<std::vector<Cell>> m_grid;
    uint32_t m_rows;
    uint32_t m_cols;
};

}  // namespace maze