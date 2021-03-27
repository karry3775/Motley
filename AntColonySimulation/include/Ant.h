#pragma once

#include <Core.h>

namespace ant_colony {
struct Ant {
    Ant(const Position& pos, const double direction, const double sense_angle,
        const double sense_direction, const double move_speed = 5,
        const uint32_t radius = 5) {
        this->pos = pos;
        this->direction = direction;
        this->sense_angle = sense_angle;
        this->sense_direction = sense_direction;
        this->move_speed = move_speed;
        this->radius = radius;
    }

    Position pos;
    double direction;
    double move_speed;
    double sense_angle;
    double sense_direction;
    double radius;
};

}  // namespace ant_colony