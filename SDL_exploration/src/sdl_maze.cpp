#include "sdl_maze.h"
#include <random>

namespace maze {

MazeGenerator::MazeGenerator() {
    // Initate the maze with default number of
    // rows and columns
    // TODO : Handle the default assignment by using default values set
    // somewhere
    m_grid = std::vector<std::vector<Cell>>(10, std::vector<Cell>(10));

    for (int row = 0; row < m_grid.size(); ++row) {
        for (int col = 0; col < m_grid[0].size(); ++col) {
            m_grid[row][col] = Cell(Point(row, col), 1);
        }
    }
}

MazeGenerator::MazeGenerator(uint32_t rows, uint32_t cols, uint32_t cell_size)
    : m_rows(rows), m_cols(cols) {
    // Initalize the size
    // Initiate the maze with rows and columns
    m_grid = std::vector<std::vector<Cell>>(m_rows, std::vector<Cell>(m_cols));

    for (int row = 0; row < m_grid.size(); ++row) {
        for (int col = 0; col < m_grid[0].size(); ++col) {
            m_grid[row][col] = Cell(Point(row, col), cell_size);
        }
    }
}

void MazeGenerator::randomizedDepthFirstSearch() {
    // Initate a visited set
    std::set<std::pair<int, int>> visited{};

    uint32_t start_row = 0;
    uint32_t start_col = 0;

    randomizedDepthFirstSearchHelper(start_row, start_col, visited);
}

void MazeGenerator::randomizedDepthFirstSearchHelper(
    uint32_t row, uint32_t col, std::set<std::pair<int, int>> visited) {
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

    // If any valid neighbours were found select one of them at
    // random
    if (!neighbours.empty()) {
        int random_idx = rand() % neighbours.size();
        // do a depth first search on that element and
        // TODO break the wall
        // between the current cell and this neigbouring cell
        visited.insert(std::make_pair(neighbours[random_idx].first,
                                      neighbours[random_idx].second));
        randomizedDepthFirstSearchHelper(neighbours[random_idx].first,
                                         neighbours[random_idx].second,
                                         visited);
    }
}

}  // end namespace maze