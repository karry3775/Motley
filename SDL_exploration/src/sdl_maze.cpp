#include "sdl_maze.h"
#include <random>
#include <iostream>  // remove later, only for DEBUG purposes

namespace maze {

const uint32_t MazeGenerator::m_default_rows = 50;
const uint32_t MazeGenerator::m_default_cols = 50;
const uint32_t MazeGenerator::m_default_size = 10;

MazeGenerator::MazeGenerator()
    : m_rows(m_default_rows), m_cols(m_default_cols), m_size(m_default_size) {
    // Initialize the grid
    initGrid();
}

MazeGenerator::MazeGenerator(uint32_t rows, uint32_t cols, uint32_t cell_size)
    : m_rows(rows), m_cols(cols) {
    // Initialize the grid
    initGrid();
}

void MazeGenerator::generateMaze() { randomizedDepthFirstSearch(); }

bool MazeGenerator::showMaze() {
    // TODO:
    /** temp : What this function should do
     * 1. First lets just write a jank piece of code
     * 2. Later we can move it to a different visualizer lib
     * 2. Render a simple window that respects the size of the grid
     * 3. Start iterating through cells and draw them ?
     */
    // Set window width and height
    uint32_t width = m_rows * m_size;
    uint32_t height = m_cols * m_size;

    // Set the color values
    SDL_Color background_color = {22, 22, 22, 255};  // Barley black
    SDL_Color line_color = {44, 44, 44, 255};        // Dark Grey

    // SDL objects
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return false;
    }

    // Create window and renderer
    if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return false;
    }

    // Set window title
    SDL_SetWindowTitle(window, "Maze");

    // Start the game loop
    SDL_bool quit = SDL_FALSE;

    while (!quit) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }  // end of poll events

        // Render the background
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                               background_color.b, background_color.a);
        SDL_RenderClear(renderer);

        // Present the render
        SDL_RenderPresent(renderer);
    }  // end of game loop

    return true;
}

void MazeGenerator::displayMazeCells() {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            std::cout << "Cell index: (" << i << ", " << j << ") " << std::endl;
            std::cout << m_grid[i][j].getWalls().top_left_top_right.exists
                      << m_grid[i][j].getWalls().top_right_bottom_right.exists
                      << m_grid[i][j].getWalls().bottom_right_bottom_left.exists
                      << m_grid[i][j].getWalls().bottom_left_top_left.exists
                      << std::endl;
            std::cout << "#####################################################"
                         "########"
                      << std::endl;
        }
    }
}

void MazeGenerator::randomizedDepthFirstSearch() {
    // Initate a visited set
    std::set<std::pair<int, int>> visited{};

    int start_row = 0;
    int start_col = 0;

    randomizedDepthFirstSearchHelper(start_row, start_col, visited);
}

void MazeGenerator::randomizedDepthFirstSearchHelper(
    int row, int col, std::set<std::pair<int, int>>& visited) {
    // Populate unvisited and valid neighbours
    std::vector<std::pair<int, int>> neighbours{};
    std::pair<int, int> cur_coords = std::make_pair(row, col);

    // unvisited and valid left neighbour (row, col - 1)
    if (col - 1 >= 0 &&
        visited.find(std::make_pair(row, col - 1)) == visited.end()) {
        neighbours.push_back(std::make_pair(row, col - 1));
    }
    // unvisited and valid right neighbour (row, col + 1)
    if (col + 1 < m_cols &&
        visited.find(std::make_pair(row, col + 1)) == visited.end()) {
        neighbours.push_back(std::make_pair(row, col + 1));
    }
    // unvisited and valid up neighbour (row - 1, col)
    if (row - 1 >= 0 &&
        visited.find(std::make_pair(row - 1, col)) == visited.end()) {
        neighbours.push_back(std::make_pair(row - 1, col));
    }
    // unvisited and valid down neighbour (row + 1, col)
    if (row + 1 < m_rows &&
        visited.find(std::make_pair(row + 1, col)) == visited.end()) {
        neighbours.push_back(std::make_pair(row + 1, col));
    }

    while (!neighbours.empty()) {
        // Select neighbours at random while there are neighbours remaining
        int random_idx = rand() % neighbours.size();
        // Need to check if this neighbour has already been visited by the
        // children
        if (visited.find(std::make_pair(neighbours[random_idx].first,
                                        neighbours[random_idx].second)) !=
            visited.end()) {
            // remove that from neighbours
            neighbours.erase(neighbours.begin() + random_idx);
            continue;
        }
        // do a depth first search on that element and
        // break the wall

        // If we have a top neighbour
        // TODO we can use simply indices to determine which neighbour it is:
        if (neighbours[random_idx].first < row) {
            m_grid[row][col].getWallsMutable().top_left_top_right.destroy();
            m_grid[neighbours[random_idx].first][neighbours[random_idx].second]
                .getWallsMutable()
                .bottom_right_bottom_left.destroy();
        }
        // If we a right neighbour
        else if (neighbours[random_idx].second > col) {
            m_grid[row][col].getWallsMutable().top_right_bottom_right.destroy();
            m_grid[neighbours[random_idx].first][neighbours[random_idx].second]
                .getWallsMutable()
                .bottom_left_top_left.destroy();
        }
        // If we have a left neighbour
        else if (neighbours[random_idx].second < col) {
            m_grid[row][col].getWallsMutable().bottom_left_top_left.destroy();
            m_grid[neighbours[random_idx].first][neighbours[random_idx].second]
                .getWallsMutable()
                .top_right_bottom_right.destroy();
        }
        // if we have down neighbour
        else {
            m_grid[row][col]
                .getWallsMutable()
                .bottom_right_bottom_left.destroy();
            m_grid[neighbours[random_idx].first][neighbours[random_idx].second]
                .getWallsMutable()
                .top_left_top_right.destroy();
        }

        // between the current cell and this neigbouring cell
        visited.insert(std::make_pair(neighbours[random_idx].first,
                                      neighbours[random_idx].second));
        randomizedDepthFirstSearchHelper(neighbours[random_idx].first,
                                         neighbours[random_idx].second,
                                         visited);
        // remove the curent neighbour from  the vector
        neighbours.erase(neighbours.begin() + random_idx);
    }
}

void MazeGenerator::initGrid() {
    m_grid = std::vector<std::vector<Cell>>(m_rows, std::vector<Cell>(m_cols));

    for (int row = 0; row < m_grid.size(); ++row) {
        for (int col = 0; col < m_grid[0].size(); ++col) {
            m_grid[row][col] = Cell(Point(row * m_size, col * m_size), 1);
        }
    }
}

}  // end namespace maze
