#pragma once

#include <vector>
#include <unordered_map>

namespace maze {

struct Point {
    int x;
    int y;

    Point();

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct Wall {
    Point start;
    Point end;

    Wall();

    Wall(Point start, Point end) {
        this->start = start;
        this->end = end;
    }
};

struct Walls {
    Wall top_left_top_right;
    Wall top_right_bottom_right;
    Wall bottom_right_bottom_left;
    Wall bottom_left_top_left;

    Walls();

    Walls(Wall tltr, Wall trbr, Wall brbl, Wall bltl) {
        top_left_top_right = tltr;
        top_right_bottom_right = trbr;
        bottom_right_bottom_left = brbl;
        bottom_left_top_left = bltl;
    }
};

struct Corners {
    Point top_left;
    Point top_right;
    Point bottom_left;
    Point bottom_right;

    Corners();

    Corners(Point top_left, Point top_right, Point bottom_left,
            Point bottom_right) {
        this->top_left = top_left;
        this->top_right = top_right;
        this->bottom_left = bottom_left;
        this->bottom_right = bottom_right;
    }
};

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
    Cell(Point origin, uint32_t size){};

    /**
     * A getter function to retrieve
     * origin of the cell
     */
    inline const Point& getOrigin() const { return m_origin; }

    /**
     * A getter function to retrieve
     * size of the cell
     */
    inline const uint32_t& getSize() const { return m_size; }

    /**
     * A getter function to retrieve
     * corners of the cell
     */
    inline const Corners& getCorners() const { return m_corners; }

    /**
     * A getter function to retrieve
     * walls of the cells
     */
    inline const Walls& getWalls() const { return m_walls; }

    static const Point
        default_origin;  // will be set in the implementation file
    static const uint32_t
        default_size;  // will be set in the implementation file

   private:
    Point m_origin;
    uint32_t m_size;
    Corners m_corners;
    Walls m_walls;

    /**
     * Utiility function to construct the cell
     * fron origin and size
     */
    void setCellFromOriginAndSize();

    /**
     * A setter function to set the origin
     * of the cell
     */
    inline void setOrigin(const Point& origin) { m_origin = origin; }

    /**
     * A setter function to set the size of
     * the cell
     */
    inline void setSize(const uint32_t& size) { m_size = size; }

    /**
     * A setter function to set the corners
     * of a cell
     */
    inline void setCorners(const Corners& corners) { m_corners = corners; }

    /**
     * A setter function to set the walls for
     * a cell
     */
    inline void setWalls(const Walls& walls) { m_walls = walls; }
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