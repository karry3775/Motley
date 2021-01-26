#include "sdl_maze.h"
#include <random>

namespace maze {

const uint32_t MazeGenerator::m_default_rows = 10;
const uint32_t MazeGenerator::m_default_cols = 10;
const uint32_t MazeGenerator::m_default_size = 1;

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

    while (!neighbours.empty()) {
        // Select neighbours at random while there are neighbours remaining
        int random_idx = rand() % neighbours.size();
        // do a depth first search on that element and
        // TODO break the wall
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