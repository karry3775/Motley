#include "sdl_maze.h"
#include <random>
#include <iostream>  // remove later, only for DEBUG purposes
#include <unistd.h>  // not portable will switch to boost in later iterations

namespace maze {

const uint32_t MazeGenerator::m_default_rows = 20;
const uint32_t MazeGenerator::m_default_cols = 20;
const uint32_t MazeGenerator::m_default_size = 50;
const uint32_t MazeGenerator::m_padding = 1;
const uint32_t MazeGenerator::m_sleep_duration_ms =
    0.1 * microseconds_in_seconds;  // refers

MazeGenerator::MazeGenerator()
    : m_rows(m_default_rows), m_cols(m_default_cols), m_size(m_default_size) {
    // Initialize the grid
    if (!initGrid()) {
        // TODO : Add glog
    }
}

MazeGenerator::MazeGenerator(uint32_t rows, uint32_t cols, uint32_t cell_size)
    : m_rows(rows), m_cols(cols) {
    // Initialize the grid
    if (!initGrid()) {
        // TODO : Add glog
    }
}

void MazeGenerator::generateMaze() { randomizedDepthFirstSearch(); }

bool MazeGenerator::showMaze() {
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

        // Render and Present Maze
        renderAndPresentMaze();

    }  // end of game loop

    return true;
}

void MazeGenerator::randomizedDepthFirstSearch() {
    // Initate a visited set
    std::set<std::pair<int, int>> visited{};

    int start_row = 0;
    int start_col = 0;

    // mark the first cell as visited
    visited.insert(std::make_pair(0, 0));

    randomizedDepthFirstSearchHelper(start_row, start_col, visited);
}

std::vector<std::pair<int, int>> MazeGenerator::getNeighbours(
    int row, int col, const std::set<std::pair<int, int>>& visited) {
    // Populate unvisited and valid neighbours
    std::vector<std::pair<int, int>> neighbours{};

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

    return neighbours;
}

void MazeGenerator::destroySharedWall(
    std::vector<std::pair<int, int>> neighbours, int idx, int row, int col) {
    // If we have a top neighbour
    // TODO we can use simply indices to determine which neighbour it is:
    if (neighbours[idx].first < row) {
        m_grid[row][col].getWallsMutable().top_left_top_right.destroy();
        m_grid[neighbours[idx].first][neighbours[idx].second]
            .getWallsMutable()
            .bottom_right_bottom_left.destroy();
    }
    // If we have a right neighbour
    else if (neighbours[idx].second > col) {
        m_grid[row][col].getWallsMutable().top_right_bottom_right.destroy();
        m_grid[neighbours[idx].first][neighbours[idx].second]
            .getWallsMutable()
            .bottom_left_top_left.destroy();
    }
    // If we have a left neighbour
    else if (neighbours[idx].second < col) {
        m_grid[row][col].getWallsMutable().bottom_left_top_left.destroy();
        m_grid[neighbours[idx].first][neighbours[idx].second]
            .getWallsMutable()
            .top_right_bottom_right.destroy();
    }
    // If we have down neighbour
    else {
        m_grid[row][col].getWallsMutable().bottom_right_bottom_left.destroy();
        m_grid[neighbours[idx].first][neighbours[idx].second]
            .getWallsMutable()
            .top_left_top_right.destroy();
    }
}

void MazeGenerator::randomizedDepthFirstSearchHelper(
    int row, int col, std::set<std::pair<int, int>>& visited) {
    // render and present the maze
    renderAndPresentMaze();

    // Get valid neighbours
    auto neighbours = getNeighbours(row, col, visited);

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

        // break shared wall
        destroySharedWall(neighbours, random_idx, row, col);

        // Mark current neighbour as visited
        visited.insert(std::make_pair(neighbours[random_idx].first,
                                      neighbours[random_idx].second));

        // Recursively do a randomized depth first search
        randomizedDepthFirstSearchHelper(neighbours[random_idx].first,
                                         neighbours[random_idx].second,
                                         visited);
        // remove the curent neighbour from  the vector
        neighbours.erase(neighbours.begin() + random_idx);
    }
}

bool MazeGenerator::initGrid() {
    m_grid = std::vector<std::vector<Cell>>(m_rows, std::vector<Cell>(m_cols));

    for (int row = 0; row < m_grid.size(); ++row) {
        for (int col = 0; col < m_grid[0].size(); ++col) {
            m_grid[row][col] = Cell(Point(row * m_size, col * m_size), m_size);
        }
    }

    // Set visualizer params
    m_width_in_pix = m_rows * m_size + m_padding;
    m_height_in_pix = m_cols * m_size + m_padding;

    // Set the color values
    m_background_color = {22, 22, 22, 255};  // Barley black
    m_line_color = {255, 255, 255, 255};     // White

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return false;
    }

    // Create window and renderer
    if (SDL_CreateWindowAndRenderer(m_width_in_pix, m_height_in_pix, 0,
                                    &m_window, &m_renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return false;
    }

    // Set Window title
    SDL_SetWindowTitle(m_window, "Maze");

    return true;
}

void MazeGenerator::renderAndPresentMaze() {
    // Render the background
    SDL_SetRenderDrawColor(m_renderer, m_background_color.r,
                           m_background_color.g, m_background_color.b,
                           m_background_color.a);

    SDL_RenderClear(m_renderer);

    // Render the cell boundaries
    SDL_SetRenderDrawColor(m_renderer, m_line_color.r, m_line_color.g,
                           m_line_color.b, m_line_color.a);

    // Iterate through cells in the maze and render if the thing
    // has a wall
    for (int row = 0; row < m_rows; ++row) {
        for (int col = 0; col < m_cols; ++col) {
            // top left top right wall
            const auto tltr = m_grid[row][col].getWalls().top_left_top_right;
            if (tltr.exists) {
                // std::cout << tltr.start.x << ", " << tltr.start.y << ", "
                // << tltr.end.x << ", " << tltr.end.y << std::endl;
                SDL_RenderDrawLine(m_renderer, tltr.start.x, tltr.start.y,
                                   tltr.end.x, tltr.end.y);
            }

            // top right bottom right wall
            const auto trbr =
                m_grid[row][col].getWalls().top_right_bottom_right;
            if (trbr.exists) {
                SDL_RenderDrawLine(m_renderer, trbr.start.x, trbr.start.y,
                                   trbr.end.x, trbr.end.y);
            }

            // bottom right bottom left wall
            const auto brbl =
                m_grid[row][col].getWalls().bottom_right_bottom_left;
            if (brbl.exists) {
                SDL_RenderDrawLine(m_renderer, brbl.start.x, brbl.start.y,
                                   brbl.end.x, brbl.end.y);
            }

            // bottom left and top left wall
            const auto bltl = m_grid[row][col].getWalls().bottom_left_top_left;
            if (bltl.exists) {
                SDL_RenderDrawLine(m_renderer, bltl.start.x, bltl.start.y,
                                   bltl.end.x, bltl.end.y);
            }
        }
    }

    // Present the render
    SDL_RenderPresent(m_renderer);

    // Add an artificial pause
    usleep(m_sleep_duration_ms);
}

}  // end namespace maze
