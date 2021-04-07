#pragma once

#include <glog/logging.h>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <list>
#include <time.h>
#include <iostream>
#include <algorithm>

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
    Nest(const Position& pos, const double radius) {
        this->pos = pos;
        this->radius = radius;
    }

    Position pos;
    double radius;
};

struct Forage {
    Forage() {}
    std::vector<Position> food;
    double radius;
};

}  // namespace ant_colony