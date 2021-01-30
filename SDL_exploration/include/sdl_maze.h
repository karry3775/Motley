#pragma once

#include "sdl_maze_core.h"
#include "sdl_maze_utils.h"
#include <SDL2/SDL.h>

#define microseconds_in_seconds 1000000

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

    /**
     *  Public interface to just display grid cells
     */
    void displayMazeCells();

   private:
    /**
     * Randomized depth first search maze generation method
     */
    void randomizedDepthFirstSearch();

    /**
     *  Helper function for the above method
     */
    void randomizedDepthFirstSearchHelper(
        int row, int col, std::set<std::pair<int, int>>& visited);

    /**
     * Function to init grid
     * - assigns cells for the grid
     * - initiate the visualizer
     */
    bool initGrid();

    /**
     * Helper function to render all walls
     */
    void renderAndPresentMaze();

    std::vector<std::vector<Cell>> m_grid;
    uint32_t m_rows;
    uint32_t m_cols;
    uint32_t m_size;
    static const uint32_t m_default_rows;
    static const uint32_t m_default_cols;
    static const uint32_t m_default_size;

    // visualization members
    static const uint32_t m_padding;
    uint32_t m_width_in_pix;
    uint32_t m_height_in_pix;
    SDL_Color m_background_color;
    SDL_Color m_line_color;
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    static const uint32_t
        m_sleep_duration_ms;  // sleep duration in milliseconds
};

}  // namespace maze