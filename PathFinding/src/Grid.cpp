#include "Grid.h"

namespace pathfinding {

Grid::Grid() {
    // TODO
}

Grid::Grid(uint32_t rows, uint32_t cols, uint32_t cell_size)
    : Environment(rows * cols),
      rows_{rows},
      cols_{cols},
      cell_size_{cell_size} {
    // Add all edges
    create();
}

void Grid::create() {
    // Resize the grid matrix
    grid_.resize(rows_, std::vector<Cell*>(cols_));
    // Initialize the grid with Cells
    for(int row = 0; row < rows_; ++row) {
        for(int col = 0; col < cols_; ++col) {
            grid_[row][col] = new Cell(row, col);
        }
    }

    // Assign the adjacency list
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            // get all the neighbours of the current
            // grid cell and add the edges to the environment
            // top neighbour
            if (row - 1 >= 0) {
                addEdge(grid_[row][col], grid_[row - 1][col]);
            }
            // bottom neighbour
            if (row + 1 < rows_) {
                addEdge(grid_[row][col], grid_[row + 1][col]);
            }
            // right neighbour
            if (col + 1 < cols_) {
                addEdge(grid_[row][col], grid_[row][col + 1]);
            }
            // left neighbour
            if (col - 1 >= 0) {
                addEdge(grid_[row][col], grid_[row][col - 1]);
            }
        }
    }
}

const uint32_t Grid::getRows() const { return rows_; }

const uint32_t Grid::getCols() const { return cols_; }

const uint32_t Grid::getCellSize() const { return cell_size_; }

}  // namespace pathfinding
