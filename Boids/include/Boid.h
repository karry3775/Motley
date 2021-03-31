#pragma once

#include <Core.h>

namespace boids {

struct Boid {
    Boid() {}
    Boid(const double x, const double y, const double direction)
        : x(x), y(y), direction(direction) {}

    double x;
    double y;
    double direction;
    double sense_radius;
}

}  // namespace boids