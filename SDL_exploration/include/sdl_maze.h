#pragma once

#include "sdl_maze_core.h"

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
    std::vector<std::vector<int>> m_grid;
    uint32_t m_rows;
    uint32_t m_cols;
};

}  // namespace maze