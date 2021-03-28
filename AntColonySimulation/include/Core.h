#pragma once

#include <glog/logging.h>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <list>
#include <time.h>
#include <iostream>

constexpr const uint32_t kMicrosecondsInASecond = 1000000;

namespace ant_colony {

// TODO: Add any default typedefs based on
// fundamental types here
struct Position {
    Position() {}
    Position(double x, double y) {
        this->x = x;
        this->y = y;
    }

    double x;
    double y;
};

struct Nest {
    Nest() {}
    Nest(const Position& pos, const uint32_t radius) {
        this->pos = pos;
        this->radius = radius;
    }

    Position pos;
    uint32_t radius;
};

}  // namespace ant_colony