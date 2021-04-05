#pragma once

#include <Core.h>

namespace ant_colony {
struct Ant {
    Ant(const Position& pos, const double direction, const double sense_angle,
        const double sense_direction, const double move_speed = 5,
        const double radius = 1, const int max_trail_size = 500) {
        this->pos = pos;
        this->direction = direction;
        this->sense_angle = sense_angle;
        this->sense_direction = sense_direction;
        this->move_speed = move_speed;
        this->radius = radius;
        this->max_trail_size = max_trail_size;
        this->has_salvaged = false;
    }

    Position pos;
    double direction;
    double move_speed;
    double sense_angle;
    double sense_direction;
    double radius;
    std::list<Position> trail;
    std::list<Position> seek_trail;
    std::list<Position> return_trail;
    int max_trail_size;
    bool has_salvaged;
};

}  // namespace ant_colony