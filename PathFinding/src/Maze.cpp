#include "Maze.h"

namespace pathfinding {

Maze::Maze() {
    // TODO
}

Maze::Maze(const uint32_t& rows, const uint32_t& cols,
           const uint32_t& cell_size)
    : rows_{rows}, cols_{cols}, cell_size_{cell_size} {
    // TODO
}

const uint32_t Maze::getRows() const { return rows_; }

const uint32_t Maze::getCols() const { return cols_; }

const uint32_t Maze::getCellSize() const { return cell_size_; }

Cell* Maze::at(const Cell& cell) {
    return matrix_[cell.getRow()][cell.getCol()];
}

Cell* Maze::at(const uint32_t& row, const uint32_t& col) {
    return matrix_[row][col];
}

void Maze::generate(const GenerationMethod& generation_method) {
    switch (generation_method) {
        case GenerationMethod::RANDOMIZED_DFS:
            generateRDFS();
            break;
        case GenerationMethod::PRIMS:
            generatePrims();
            break;
        case GenerationMethod::KRUSKALS:
            generateKruskal();
            break;
        default:
            LOG(FATAL) << "Unknown Maze Generation method!";
            break;
    }
}

void Maze::generateRDFS() {
    // TODO
}

void Maze::generatePrims() {
    // TODO
}

void Maze::generateKruskal() {
    // TODO
}

}  // namespace pathfinding