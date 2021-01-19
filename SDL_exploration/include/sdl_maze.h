#pragma once

#include <vector>
#include <unordered_map>

namespace maze {

typedef std::vector<int> Corners;
typedef std::unordered_map<std::pair<int, int>, std::pair<int, int>> Wall;
typedef std::vector<Wall> Walls;

class Cell {
    /**
     * The primary purpose of this class is to
     * store a cell which is represented by four
     * corners
     */
   public:
    /**
     * Default constructor which creates a cell
     * with the following default params
     * (origin = (0,0) and cell size = 1)
     * (0, 0) ------- (1, 0)
     *       |       |
     *       |       |
     * (0, 1) ------- (1, 1)
     */
    Cell(){};

    /**
     * A parameterized constructor that constructors
     * the cell from size and origin passed to it
     */
    Cell(std::pair<int, int> origin, uint32_t size){};

    /**
     * A getter function to retrieve
     * corners of the cell
     */
    const Corners& getCorners() const;

    /**
     * A getter function to retrieve
     * walls of the cells
     */
    const Walls& getWalls() const;


    static const std::pair<int, int> default_cell_origin; // will be set in the implementation file
    static const uint32_t default_cell_size; // will be set in the implementation file

   private:
    std::pair<int, int> m_cell_origin;
    uint32_t m_cell_size;
    Corners m_corners;
    Walls m_walls;

    /**
     * Utiility function to construct the cell
     * fron origin and size
     */
    void setCellFromOriginAndSize() const;

    /**
     * A setter function to set the corners
     * of a cell
     */
    void setCorners();

    /**
     * A setter function to set the walls for
     * a cell
     */
    void setWalls()
};

class MazeGenerator {
   public:
    /**
     * Constructor to initiate the Maze
     */
    MazeGenerator(uint32_t rows, uint32_t cols, uint32_t cell_size);

   private:
    std::vector<std::vector<int>> m_grid;
    uint32_t m_rows;
    uint32_t m_cols;

};

}  // end namespace maze

/** temp comment
 * Current aim is to implement a simple randomized
 * depth-first search maze generator using
 * https://en.wikipedia.org/wiki/Maze_generation_algorithm#
 * as reference. Let us not worry about visualization for now
 * and focus on just the code
 *
 * Lets first decide on how the public interface should look like
 *
 */