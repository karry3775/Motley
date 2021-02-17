#include "Maze.h"

namespace pathfinding {

Maze::Maze() {
    // TODO
}

Maze::Maze(const uint32_t& rows, const uint32_t& cols,
           const uint32_t& cell_size, const GenerationMethod& generation_method)
    : rows_{rows},
      cols_{cols},
      cell_size_{cell_size},
      generation_method_{generation_method} {
          
    // Populate the matrix_
    // Resize the grid matrix
    matrix_.resize(rows_, std::vector<Cell*>(cols_));
    // Initialize the grid with Cells
    for (int row = 0; row < rows_; ++row) {
        for (int col = 0; col < cols_; ++col) {
            matrix_[row][col] = new Cell(row, col);
        }
    }
    // Generate Maze;
    generate();
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

void Maze::generate() {
    switch (generation_method_) {
        case GenerationMethod::RANDOMIZED_DFS:
            generateRDFS();
            break;
        case GenerationMethod::PRIMS:
            generatePrims();
            break;
        case GenerationMethod::KRUSKALS:
            generateKruskal();
            break;
        case GenerationMethod::NONE:
            LOG(FATAL) << "A method needs to be specified for Maze Generation. "
                          "NONE was passed!";
            break;
        default:
            LOG(FATAL) << "Unknown Maze Generation method!";
            break;
    }
}

void Maze::generateRDFS() {
    std::set<Cell*> visited;
    Cell* start = new Cell(0, 0);

    generateRDFS(start, visited);
}

void Maze::generateRDFS(Cell* current, std::set<Cell*>& visited) {
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
            // Add a wall
            addWall(current, neighbours[random_idx]);
            continue;
        }

        // Push it into the adjaceny list
        addEdge(current, neighbours[random_idx]);

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
    } else if (cell->getRow() - 1 >= 0 && visited.find(cell) != visited.end()) {
        // Add a wall if not out of bounds but visited already
        addWall(cell, matrix_[cell->getRow() - 1][cell->getCol()]);
    }

    // Check the left neighbour
    if (cell->getCol() - 1 >= 0 && visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow()][cell->getCol() - 1]);
    } else if (cell->getCol() - 1 >= 0 && visited.find(cell) != visited.end()) {
        // Add a wall if not out of bounds but visited already
        addWall(cell, matrix_[cell->getRow()][cell->getCol() - 1]);
    }

    // Check for down neighbour
    if (cell->getRow() + 1 < matrix_.size() &&
        visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow() + 1][cell->getCol()]);
    } else if (cell->getRow() + 1 < matrix_.size() &&
               visited.find(cell) != visited.end()) {
        // Add a wall if not out of bounds but visited already
        addWall(cell, matrix_[cell->getRow() + 1][cell->getCol()]);
    }

    // Check for right neighbour
    if (cell->getCol() + 1 < matrix_[0].size() &&
        visited.find(cell) == visited.end()) {
        neighbours.emplace_back(matrix_[cell->getRow()][cell->getCol() + 1]);
    } else if (cell->getCol() + 1 < matrix_[0].size() &&
               visited.find(cell) != visited.end()) {
        // Add a wall if not out of bounds but visited already
        addWall(cell, matrix_[cell->getRow()][cell->getCol() + 1]);
    }

    return neighbours;
}

void Maze::addWall(const Cell* parent, const Cell* child) {
    // TODO: add constructs for all four wall types maybe

    // Check if its a top neighbour
    if (child->getRow() < parent->getRow()) {
        // Populate corners that will make the wall
        Corner first(parent->getRow(), parent->getCol());
        Corner second(parent->getRow(), parent->getCol() + cell_size_);
        constructWall(first, second);
    }
    // Check if its left neighbour
    else if (child->getCol() < parent->getCol()) {
        // Populate corners that will make the wall
        Corner first(parent->getRow(), parent->getCol());
        Corner second(parent->getRow() + cell_size_, parent->getCol());
        constructWall(first, second);
    }
    // Check if its down neighbour
    else if (child->getRow() > parent->getRow()) {
        // Populate corners that will make the wall
        Corner first(parent->getRow() + cell_size_, parent->getCol());
        Corner second(parent->getRow() + cell_size_,
                      parent->getCol() + cell_size_);
        constructWall(first, second);
    }
    // Otherwise handle the case for right neighbour
    else {
        // Populate corners that will make the wall
        Corner first(parent->getRow(), parent->getCol() + cell_size_);
        Corner second(parent->getRow() + cell_size_,
                      parent->getCol() + cell_size_);
        constructWall(first, second);
    }
}

void Maze::constructWall(const Corner& first, const Corner& second) {
    Wall* wall = new Wall(first, second);
    walls_.push_back(wall);
}

void Maze::generatePrims() {
    // TODO
}

void Maze::generateKruskal() {
    // TODO
}

}  // namespace pathfinding