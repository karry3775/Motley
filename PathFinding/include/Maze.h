#pragma once

#include "Cell.h"

#include "Wall.h"

#include "EnvironmentGeneration.h"

namespace pathfinding {

enum class GenerationMethod { RANDOMIZED_DFS, PRIMS, KRUSKALS };

class Maze : public Environment<Cell> {
   public:
    Maze();
    Maze(const uint32_t& rows, const uint32_t& cols, const uint32_t& cell_size);

    /**
     * Getter for the number of rows in the maze
     * @return Number of rows
     */
    const uint32_t getRows() const;

    /**
     * Getter for number of columns in the maze
     * @return Number of columns
     */
    const uint32_t getCols() const;

    /** Getter for number of cell size for the maze
     * @return size of cell in pixels
     */
    const uint32_t getCellSize() const;

    /**
     * Gets the pointer to the cell in the maze based
     * on information provided by a cell
     * @param Cell Cell describing the location to be accessed
     * @return Cell pointer for the maze
     */
    Cell* at(const Cell&);

    /**
     * Gets the pointer to the cell in the maze based
     * on row and column information
     * @param row row for the cell
     * @param col col for the cell
     * @return Cell pointer for the maze at given row and col
     */
    Cell* at(const uint32_t& row, const uint32_t& col);

   private:
    /**
     * Generate Maze based on method chosen by the user
     * @param generation_method Algorithm to be used to generate the maze
     */
    void generate(const GenerationMethod& generation_method);

    /**
     * Generate maze using RANDOMIZED_DFS
     */
    void generateRDFS();

    /**
     * Helper function for RANDOMIZED_DFS
     */
    void generateRDFS(Cell* current, std::set<Cell*>& visited);

    /**
     * Util functions for RANDOMIZED_DFS
     */
    std::vector<Cell*> getValidNeighbours(Cell* cell,
                                          const std::set<Cell*>& visited);

    /**
     * Generate maze using Prim's method
     */
    void generatePrims();

    /**
     * Generate maze using  Kruskal's method
     */
    void generateKruskal();

    // Vector of all the walls present in the maze
    std::vector<Wall*> walls_;

    // Number of rows in the maze
    uint32_t rows_;

    // Number of cols in the maze
    uint32_t cols_;

    // Size of cell in the maze
    uint32_t cell_size_;

    // Matrix that defines the maze
    std::vector<std::vector<Cell*>> matrix_;
};

}  // namespace pathfinding