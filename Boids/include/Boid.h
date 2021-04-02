#pragma once

#include <Core.h>

namespace boids {

struct Boid {
    Boid() {
        this->neighbourhood_radius = 30;
        this->neighbourhood_angle = 2 * M_PI;
        this->separation_radius = 15;
    }

    // Helper function to get distance between other boids
    double getDistance(const Boid& other) const {
        return sqrt((this->pos.x - other.pos.x) * (this->pos.x - other.pos.x) +
                    (this->pos.y - other.pos.y) * (this->pos.y - other.pos.y));
    }

    double neighbourhood_radius;
    double neighbourhood_angle;
    double separation_radius;

    Vector pos;         // position
    Vector vel;         // velocity
    Vector cohesion;    // cohesion force vector
    Vector alignment;   // alignment force vector
    Vector separation;  // sepation force vector
};

}  // namespace boids
