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
    // TODO: Later move this to a separate function
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            // get all the neighbours of the current
            // grid cell and add the edges to the environment
            // TODO: move to separate function
            // top neighbour
            if (row - 1 >= 0) {
                addEdge(Cell(row, col), Cell(row - 1, col));
            }
            // bottom neighbour
            if (row + 1 < rows_) {
                addEdge(Cell(row, col), Cell(row + 1, col));
            }
            // right neighbour
            if (col + 1 < cols_) {
                addEdge(Cell(row, col), Cell(row, col + 1));
            }
            // left neighbour
            if (col - 1 >= 0) {
                addEdge(Cell(row, col), Cell(row, col - 1));
            }
        }
    }
}

const uint32_t Grid::getRows() const { return rows_; }

const uint32_t Grid::getCols() const { return cols_; }

const uint32_t Grid::getCellSize() const { return cell_size_; }

}  // namespace pathfinding
