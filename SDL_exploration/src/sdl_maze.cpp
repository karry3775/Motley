#include "sdl_maze.h"

namespace maze {

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

}  // end namespace maze