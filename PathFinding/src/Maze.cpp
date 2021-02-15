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
    // temp : brainstorm about the technique
    // We start from a starting cell and then we do randomized DFS
    std::set<Cell*> visited;
    Cell* start = new Cell(0, 0);

    generateRDFS(start, visited);
}

/**
 * TODO: Should populate the walls
 * TODO: Should populate the adjacency list for path finding algorithms
 *    to work upon
 */
void Maze::generateRDFS(Cell* current, std::set<Cell*>& visited) {
    // base case
    // TODO:

    // Select one of the unvisited valid neighbour
    auto neighbours = getValidNeighbours(current, visited);

    // Select one at random to be searched for
    // and remove that from the neighbours when done
    while (!neighbours.empty()) {
        // Select one index at random
        int random_idx = rand() % neighbours.size();

        // Check if the current random_idx is still visitable
        // since the children might have already visited it
        if (visited.find(neighbours[random_idx]) != visited.end()) {
            // Remove this neighbour
            neighbours.erase(neighbours.begin() + random_idx);
            continue;
        }
        // Mark it as visited
        visited.insert(neighbours[random_idx]);

        // Recurse
        generateRDFS(neighbours[random_idx], visited);

        // Remove the current neighbour
        neighbours.erase(neighbours.begin() + random_idx);
    }
}

std::vector<Cell*> Maze::getValidNeighbours(Cell* cell,
                                            const std::set<Cell*>& visited) {
    std::vector<Cell*> neighbours;

    // Check the top neighbour
    if (cell->getRow() - 1 >= 0 && visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow() - 1][cell->getCol()]);
    }

    // Check the left neighbour
    if (cell->getCol() - 1 >= 0 && visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow()][cell->getCol() - 1]);
    }

    // Check for down neighbour
    if (cell->getRow() + 1 < matrix_.size() &&
        visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow() + 1][cell->getCol()]);
    }

    // Check for right neighbour
    if (cell->getCol() + 1 < matrix_[0].size() &&
        visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow()][cell->getCol() + 1]);
    }

    return neighbours;
}

void Maze::generatePrims() {
    // TODO
}

void Maze::generateKruskal() {
    // TODO
}

}  // namespace pathfinding