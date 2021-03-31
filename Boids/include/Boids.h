#pragma once

#include <Core.h>
#include <Boid.h>
#include <Visualization.h>

namespace boids {
class Boids {
   public:
    Boids();
    Boids(int num_boids);
    void show();

   private:
    void initBoids();

    // some viz related functions
    void updateBoids(int interval);
    void renderCurrentBuffer();
    void boxBlur();

    std::vector<Boid> boids_;
    Viz viz_;
};

}  // namespace boids