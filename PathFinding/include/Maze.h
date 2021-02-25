#pragma once

#include "Cell.h"

#include "Wall.h"

#include "EnvironmentGeneration.h"

namespace pathfinding {

enum class MazeGenerationMethod { RANDOMIZED_DFS, PRIMS, KRUSKALS };

class Maze : public Environment<Cell> {
   public:
    Maze();
    Maze(const uint32_t& rows, const uint32_t& cols, const uint32_t& cell_size,
         const MazeGenerationMethod& generation_method);

    /**
     * Getter for the number of rows in the maze
     * @return Number of rows
     */
    virtual const uint32_t getRows() const override;

    /**
     * Getter for number of columns in the maze
     * @return Number of columns
     */
    virtual const uint32_t getCols() const override;

    /** Getter for number of cell size for the maze
     * @return size of cell in pixels
     */
    virtual const uint32_t getCellSize() const override;

    /**
     * Getter for walls of the maze
     */
    virtual const std::vector<Wall*> getWalls() const override;

    /**
     * Gets the pointer to the cell in the maze based
     * on information provided by a cell
     * @param Cell Cell describing the location to be accessed
     * @return Cell pointer for the maze
     */
    virtual Cell* at(const Cell&) override;

    /**
     * Gets the pointer to the cell in the maze based
     * on row and column information
     * @param row row for the cell
     * @param col col for the cell
     * @return Cell pointer for the maze at given row and col
     */
    virtual Cell* at(const uint32_t& row, const uint32_t& col) override;

   private:
    /**
     * Generate Maze based on method chosen by the user     *
     */
    void generate();

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
     * Adds a wall between two cells
     * @param parent parent cell under consideration
     * @param child child (aka neighbour) cell under consideration
     */
    void addWall(const Cell* parent, const Cell* child);

    /**
     * Construct wall defined by two corners
     * @param first first corner of the wall
     * @param second second corner of the wall
     */
    void constructWall(const Corner& first, const Corner& second);

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

    // Method used for maze generation
    MazeGenerationMethod generation_method_;
};

}  // namespace pathfinding