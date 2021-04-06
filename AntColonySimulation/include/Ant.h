#pragma once

#include <Core.h>

namespace ant_colony {
struct Ant {
    Ant(const Position& pos, const double direction, const double sense_radius,
        const double move_speed = 5, const double radius = 1.25,
        const int max_trail_size = 500) {
        this->pos = pos;
        this->direction = direction;
        this->sense_radius = sense_radius;
        this->move_speed = move_speed;
        this->radius = radius;
        this->max_trail_size = max_trail_size;
        this->has_salvaged = false;
    }

    Position pos;
    double direction;
    double move_speed;
    double sense_radius;
    double radius;
    std::list<Position> trail;
    std::list<Position> seek_trail;
    std::list<Position> return_trail;
    int max_trail_size;
    bool has_salvaged;
};

}  // namespace ant_colony