#pragma once

#include <Core.h>

namespace boids {
class Boids {
   public:
    Boids();
    Boids(int num_boids);

   private:
    std::vector<Boid> boids_;
}

}  // namespace boids