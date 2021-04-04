#pragma once

#include <SDL2/SDL.h>
#include <glog/logging.h>
#include <vector>
#include <memory>

namespace boids {

struct Vector {
    Vector() {}
    Vector(double x, double y) {
        this->x = x;
        this->y = y;
    }

    void normalize() {
        double norm = sqrt(x * x + y * y);

        if (norm == 0) return;

        x = x / norm;
        y = y / norm;
    }

    bool operator+=(const Vector& other) {
        x = x + other.x;
        y = y + other.y;
    }

    Vector operator*(const double factor) const {
        return Vector(this->x * factor, this->y * factor);
    }

    Vector operator+(const Vector& other) const {
        return Vector(this->x + other.x, this->y + other.y);
    }

    double x, y;
};

inline double getRandWithin(double min_val, double max_val) {
    double rand_number =
        (double(rand()) / RAND_MAX) * (max_val - min_val) + min_val;

    return rand_number;
}

}  // namespace boids