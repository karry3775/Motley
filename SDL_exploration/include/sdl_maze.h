#pragma once

#include "sdl_maze_core.h"
#include "sdl_maze_utils.h"
#include <SDL2/SDL.h>

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

    /**
     * Public interface function that helps the user to create
     * a maze. Will be responsible for making calls to maze generation
     * algorithms.
     */
    void generateMaze();

    /**
     * Public interface function to show the generated maze
     */
    bool showMaze();

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

    /**
     * Function to init grid
     * - assigns cells for the grid
     * - to add more ...
     */
    void initGrid();

    std::vector<std::vector<Cell>> m_grid;
    uint32_t m_rows;
    uint32_t m_cols;
    uint32_t m_size;
    static const uint32_t m_default_rows;
    static const uint32_t m_default_cols;
    static const uint32_t m_default_size;
};

}  // namespace maze