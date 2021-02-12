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
    matrix_.resize(rows_, std::vector<Cell*>(cols_));
    // Initialize the grid with Cells
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            matrix_[row][col] = new Cell(row, col);
        }
    }

    // Assign the adjacency list
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            // get all the neighbours of the current
            // grid cell and add the edges to the environment
            // top neighbour
            if (row - 1 >= 0) {
                addEdge(matrix_[row][col], matrix_[row - 1][col]);
            }
            // bottom neighbour
            if (row + 1 < rows_) {
                addEdge(matrix_[row][col], matrix_[row + 1][col]);
            }
            // right neighbour
            if (col + 1 < cols_) {
                addEdge(matrix_[row][col], matrix_[row][col + 1]);
            }
            // left neighbour
            if (col - 1 >= 0) {
                addEdge(matrix_[row][col], matrix_[row][col - 1]);
            }
        }
    }
}

const uint32_t Grid::getRows() const { return rows_; }

const uint32_t Grid::getCols() const { return cols_; }

const uint32_t Grid::getCellSize() const { return cell_size_; }

Cell* Grid::at(const Cell& cell) {
    return matrix_[cell.getRow()][cell.getCol()];
}

Cell* Grid::at(const uint32_t& row, const uint32_t& col) {
    return matrix_[row][col];
}

}  // namespace pathfinding
