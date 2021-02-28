#pragma once

#include "Core.h"

namespace pathfinding {
class Cell {
   public:
    Cell(){};
    Cell(const int32_t& row, const int32_t& col) : row_{row}, col_{col} {};

    /**
     * Compare operator for Cell. Essential for this be considered as a key in
     * any map data structure
     */
    bool operator<(const Cell& c) const {
        return (this->row_ <= c.row_ && this->col_ <= c.col_);
    }

    bool operator==(const Cell& c) const {
        return (this->row_ == c.row_ && this->col_ == c.col_);
    }

    bool operator!=(const Cell& c) const {
        return (this->row_ != c.row_ || this->col_ != c.col_);
    }

    /**
     * Getter for row for the cell
     * @return row for the cell
     */
    const int32_t getRow() const { return row_; }

    /** Getter for columm for the cell
     * @return column for the cell
     */
    const int64_t getCol() const { return col_; }

   private:
    int32_t row_;
    int32_t col_;
};

// Major Gotcha! Not using inline causes multiple definitions of <<
// TODO: Find out what causes this
inline std::ostream& operator<<(std::ostream& stream, const Cell& c) {
    stream << "Cell : ( " << c.getRow() << ", " << c.getCol() << ") ";
    return stream;
}

}  // namespace pathfinding