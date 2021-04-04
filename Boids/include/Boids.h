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

    // Functions that define boids rules
    Vector getSeparationVector(const Boid& boid,
                               const std::vector<Boid>& neighbours);
    Vector getAlignmentVector(const Boid& boid,
                              const std::vector<Boid>& neighbours);
    Vector getCohesionVector(const Boid& boid,
                             const std::vector<Boid>& neighbours);

    // Helper functions
    std::vector<Boid> getNeighbours(const Boid& boid);

    // some viz related functions
    void updateBoids(int interval);
    void renderCurrentBuffer();
    void boxBlur();

    std::vector<Boid> boids_;
    Viz viz_;

    // Max velocity
    static const double max_vel;
};

}  // namespace boids