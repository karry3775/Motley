#include "sdl_maze_utils.h"

namespace maze {
Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Wall::Wall() {
    start = Point(0, 0);
    end = Point(0, 1);
    exists = true;
}

Wall::Wall(Point start, Point end) {
    this->start = start;
    this->end = end;
    // Set exists to true by default
    exists = true;
}

void Wall::destroy() { exists = false; }

Walls::Walls() {
    top_left_top_right = Wall(Point(0, 0), Point(1, 0));
    top_right_bottom_right = Wall(Point(1, 0), Point(1, 1));
    bottom_right_bottom_left = Wall(Point(1, 1), Point(0, 1));
    bottom_left_top_left = Wall(Point(0, 1), Point(0, 0));
}

Walls::Walls(Wall tltr, Wall trbr, Wall brbl, Wall bltl) {
    top_left_top_right = tltr;
    top_right_bottom_right = trbr;
    bottom_right_bottom_left = brbl;
    bottom_left_top_left = bltl;
}

Corners::Corners() {
    top_left = Point(0, 0);
    top_right = Point(1, 0);
    bottom_left = Point(0, 1);
    bottom_right = Point(1, 1);
}

Corners::Corners(Point top_left, Point top_right, Point bottom_left,
                 Point bottom_right) {
    this->top_left = top_left;
    this->top_right = top_right;
    this->bottom_left = bottom_left;
    this->bottom_right = bottom_right;
}

Cell::Cell() {
    setOrigin(Point(0, 0));
    setSize(1);
    setCellFromOriginAndSize();
}

Cell::Cell(Point origin, uint32_t size) : m_origin(origin), m_size(size) {
    setCellFromOriginAndSize();
}

void Cell::setCellFromOriginAndSize() {
    // Assign corner points from origin and size
    Point top_left(m_origin.x, m_origin.y);
    Point top_right(m_origin.x, m_origin.y + m_size);
    Point bottom_left(m_origin.x + m_size, m_origin.y);
    Point bottom_right(m_origin.x + m_size, m_origin.y + m_size);

    // Create and set Corners type object for Cell
    Corners corners(top_left, top_right, bottom_left, bottom_right);
    setCorners(corners);

    // Set the walls
    // There are going to be four walls associated with each cell
    // top left -> top right
    Wall top_left_top_right(top_left, top_right);
    // top right -> bottom right
    Wall top_right_bottom_right(top_right, bottom_right);
    // bottom right -> bottom left
    Wall bottom_right_bottom_left(bottom_right, bottom_left);
    // bottom left -> top left
    Wall bottom_left_top_left(bottom_left, top_left);

    // Create and set Walls type object for Cell
    Walls walls(top_left_top_right, top_right_bottom_right,
                bottom_right_bottom_left, bottom_left_top_left);
    setWalls(walls);
}

}  // namespace maze
