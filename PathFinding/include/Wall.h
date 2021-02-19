#pragma once

#include "Core.h"

#include "Corner.h"

namespace pathfinding {

class Wall {
   public:
    Wall(const Corner&, const Corner&);
    ~Wall();

    std::set<Corner> getItems() const { return items_; }

    void print() const {
        for (auto itr = items_.begin(); itr != items_.end(); ++itr) {
            std::cout << *itr << " ";
        }
        std::cout << std::endl;
    }

   private:
    // To store the wall items (i.e. the two Cells, forming
    // the walls)
    std::set<Corner> items_;
};

// FIXME: I am not working as expected
inline std::ostream& operator<<(std::ostream& stream, const Wall& wall) {
    stream << "Wall: ";

    std::set<Corner> items;
    for (auto itr = items.begin(); itr != items.end(); ++itr) {
        stream << (*itr) << " ";
    }

    return stream;
}

}  // namespace pathfinding