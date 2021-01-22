#include "sdl_maze_utils.h"

namespace maze {
Point::Point() {}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Wall::Wall() {}

Wall::Wall(Point start, Point end) {
    this->start = start;
    this->end = end;
}

Walls::Walls() {}

Walls::Walls(Wall tltr, Wall trbr, Wall brbl, Wall bltl) {
    top_left_top_right = tltr;
    top_right_bottom_right = trbr;
    bottom_right_bottom_left = brbl;
    bottom_left_top_left = bltl;
}

Corners::Corners() {}

Corners::Corners(Point top_left, Point top_right, Point bottom_left,
                 Point bottom_right) {
    this->top_left = top_left;
    this->top_right = top_right;
    this->bottom_left = bottom_left;
    this->bottom_right = bottom_right;
}

Cell::Cell() {
    // TODO
}

Cell::Cell(Point origin, uint32_t size) {
    // TODO
}

void Cell::setCellFromOriginAndSize() {
    // Assign corner points from origin and size
    Point top_left(m_origin.x, m_origin.y);
    Point top_right(m_origin.x + m_size, m_origin.y);
    Point bottom_left(m_origin.x, m_origin.y + m_size);
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
