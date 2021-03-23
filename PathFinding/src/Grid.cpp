#include "Grid.h"

namespace pathfinding {

Grid::Grid() {
    // TODO
}

Grid::Grid(const uint32_t& rows, const uint32_t& cols,
           const uint32_t& cell_size,
           const ObstacleGenerationMethod& obs_gen_method,
           const double& obstacle_perc)
    : Environment(rows * cols),
      rows_{rows},
      cols_{cols},
      cell_size_{cell_size},
      obs_gen_method_{obs_gen_method} {
    // Check if num obstacles specified are valid
    CHECK(obstacle_perc <= 1.0)
        << " Obstacle percentage cannot more than 100%!";

    // Calculate the number of obstalces
    num_obstacles_ = static_cast<uint32_t>((rows_ * cols_) * obstacle_perc);

    // Initialize obstacles matrix with zero
    obstacles_.resize(rows_,
                      std::vector<int>(cols_, 0));  // 0 means not occupied

    switch (obs_gen_method_) {
        case ObstacleGenerationMethod::MANUAL:
            break;
        case ObstacleGenerationMethod::FISHER_YATES_SHUFFLE:
            generateObstacles();
            break;
        default:
            LOG(FATAL) << "Unknown obstacle generation method specified!";
            break;
    }

    // Create grid
    generate();
}

void Grid::generate() {
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
            // grid cell which are not obstacles and add the edges to the
            // environment

            // Skip if current row, col is an obstacle
            if (obstacles_[row][col] == 1) continue;

            // top neighbour
            if (row - 1 >= 0 && obstacles_[row - 1][col] != 1) {
                addEdge(matrix_[row][col], matrix_[row - 1][col]);
            }
            // bottom neighbour
            if (row + 1 < rows_ && obstacles_[row + 1][col] != 1) {
                addEdge(matrix_[row][col], matrix_[row + 1][col]);
            }
            // right neighbour
            if (col + 1 < cols_ && obstacles_[row][col + 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row][col + 1]);
            }
            // left neighbour
            if (col - 1 >= 0 && obstacles_[row][col - 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row][col - 1]);
            }

            // top right neighbour
            if (row - 1 >= 0 && col + 1 < cols_ &&
                obstacles_[row - 1][col + 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row - 1][col + 1]);
            }
            // top left neighbour
            if (row - 1 >= 0 && col - 1 >= 0 &&
                obstacles_[row - 1][col - 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row - 1][col - 1]);
            }
            // bottom right neighbour
            if (row + 1 < rows_ && col + 1 < cols_ &&
                obstacles_[row + 1][col + 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row + 1][col + 1]);
            }
            // bottom left neighbour
            if (row + 1 < rows_ && col - 1 >= 0 &&
                obstacles_[row + 1][col - 1] != 1) {
                addEdge(matrix_[row][col], matrix_[row + 1][col - 1]);
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

void Grid::pushObstacles(const uint32_t& row, const uint32_t& col) {
    CHECK(!obstacles_.empty()) << "Obstacles were not initialized with a size!";

    obstacles_[row][col] = 1;
}

std::vector<std::vector<int>> Grid::getObstacles() const { return obstacles_; }

void Grid::generateObstacles() {
    CHECK(obs_gen_method_ == ObstacleGenerationMethod::FISHER_YATES_SHUFFLE)
        << " Only supports fisher yates algorithm for now!";

    std::vector<Cell> cell_coords{};

    // Push in all the Cell coordinates
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            cell_coords.push_back(Cell(i, j));
        }
    }

    // Shuffle the cell coords
    for (int i = 0; i < cell_coords.size(); ++i) {
        // Generate a random number between i and cell_coords size - 1
        // inclusive of max and min
        int min = i;
        int max = cell_coords.size() - 1;
        int random_idx = rand() % (max - min + 1) + min;

        // Swap the random index with current index
        Cell temp = cell_coords[i];
        cell_coords[i] = cell_coords[random_idx];
        cell_coords[random_idx] = temp;
    }

    // Iterate through the shuffled obstacles and push the first
    // n obstacles in the obstacles matrix
    for (int i = 0; i < num_obstacles_; ++i) {
        pushObstacles(cell_coords[i].getRow(), cell_coords[i].getCol());
    }
}

}  // namespace pathfinding
