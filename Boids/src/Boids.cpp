#include <Boids.h>
#include <iostream>

namespace boids {

const double Boids::max_vel = 1;

constexpr double turnfactor = 1.0;
constexpr double inv_sep_wt = 40.0;
constexpr double inv_ali_wt = 60.0;
constexpr double inv_coh_wt = 600.0;
constexpr double boid_radius = 1.5;
constexpr double padding = 5;

Boids::Boids(int num_boids) {
    // Initialize a seed
    srand(time(NULL));
    // resize the boid vector
    boids_.resize(num_boids);
    // Initialize boids randomly
    initBoids();
}

void Boids::initBoids() {
    for (auto& boid : boids_) {
        // Assign random position
        boid.pos =
            Vector(getRandWithin(0, viz_.width), getRandWithin(0, viz_.height));
        // Assign random velocity
        boid.vel = Vector(getRandWithin(-3, 3), getRandWithin(-3, 3));
    }
}

void Boids::show() {
    // Game loop
    SDL_bool quit = SDL_FALSE;

    int last_time = -1.0;

    while (!quit) {
        int time_elapsed = SDL_GetTicks();
        if (last_time == -1) last_time = time_elapsed;
        int interval = time_elapsed - last_time;
        last_time = time_elapsed;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }
        // Update and set pixel colors for boids
        updateBoids(interval);

        // render Buffer
        viz_.renderCurrentBuffer();

        // box blur
        viz_.boxBlur();
    }

    viz_.destroy();
}

void Boids::updateBoids(int interval) {
    for (auto& boid : boids_) {
        int time_elapsed = SDL_GetTicks();
        double green_factor = sin(time_elapsed * 0.0001);
        double red_factor = sin(time_elapsed * 0.0001 + M_PI / 4);
        double blue_factor = sin(time_elapsed * 0.0003 + M_PI / 8);
        Uint8 red = 5 + Uint8(abs(255 * red_factor));
        Uint8 green = 5 + Uint8(abs(255 * green_factor));
        Uint8 blue = 5 + Uint8(abs(255 * blue_factor));

        // viz_.setPixelColor(boid.x, boid.y, red, green, blue);

        for (int x = -boid_radius; x < boid_radius; ++x) {
            for (int y = -boid_radius; y < boid_radius; ++y) {
                if (x * x + y * y <= boid_radius * boid_radius) {
                    viz_.setPixelColor(x + boid.pos.x, y + boid.pos.y, red,
                                       green, blue);
                }
            }
        }

        // Update boid location based on the three rules

        // First thing is to get the neighbours out
        const auto neighbours = getNeighbours(boid);
        // Rule 1:  Separation -- for boids in the neighbour, try
        // to not to get too close to them

        // Get separation vector
        auto separation = getSeparationVector(boid, neighbours);
        // Rule 2: Alignment --  Set the heading to be equal to average
        // heading of the neighbour hood
        auto alignment = getAlignmentVector(boid, neighbours);

        // Rule 3: Cohesion -- Steer to move towards average location of the
        // neighbour
        auto cohesion = getCohesionVector(boid, neighbours);

        auto randV = Vector(getRandWithin(-0.2, 0.2), getRandWithin(-0.2, 0.2));

        // Update velocity
        boid.vel += separation + alignment + cohesion + randV;

        boid.vel.x = std::min(max_vel, boid.vel.x);
        boid.vel.y = std::min(max_vel, boid.vel.y);

        // Update position
        boid.pos += boid.vel;

        if (boid.pos.x < padding) {
            boid.vel.x = 1;
        } else if (boid.pos.x > viz_.width - padding) {
            boid.vel.x = -1;
        }

        if (boid.pos.y < padding) {
            boid.vel.y = 1;
        } else if (boid.pos.y > viz_.height - padding) {
            boid.vel.y = -1;
        }
    }
}

Vector Boids::getSeparationVector(const Boid& boid,
                                  const std::vector<Boid>& neighbours) {
    Vector sep;

    // Return zero vector if no neighbours
    if (neighbours.empty()) return sep;

    // Get the average vector that points in away from these neighbours

    for (const auto& ngh : neighbours) {
        auto current_dist = boid.getDistance(ngh);
        if (current_dist < boid.separation_radius) {
            // Find the vector pointing towards the incoming boid
            Vector inwards =
                Vector(boid.pos.x - ngh.pos.x, boid.pos.y - ngh.pos.y);
            sep += inwards;
        }
    }

    // normalize separation vector
    sep.x /= inv_sep_wt;
    sep.y /= inv_sep_wt;

    return sep;
}

Vector Boids::getAlignmentVector(const Boid& boid,
                                 const std::vector<Boid>& neighbours) {
    Vector ali;

    // Return zero vector if no neighbours
    if (neighbours.empty()) return ali;

    for (const auto& ngh : neighbours) {
        ali += ngh.vel;
    }

    // Normalize
    ali.x /= neighbours.size();
    ali.y /= neighbours.size();

    return Vector((ali.x - boid.vel.x) / inv_ali_wt,
                  (ali.y - boid.vel.y) / inv_ali_wt);
}

Vector Boids::getCohesionVector(const Boid& boid,
                                const std::vector<Boid>& neighbours) {
    Vector coh;

    // Return zero vector if no neighbours
    if (neighbours.empty()) return coh;

    for (const auto& ngh : neighbours) {
        coh += ngh.pos;
    }

    // Normalize
    coh.x /= neighbours.size();
    coh.y /= neighbours.size();

    return Vector((coh.x - boid.pos.x) / inv_coh_wt,
                  (coh.y - boid.pos.y) / inv_coh_wt);
}
std::vector<Boid> Boids::getNeighbours(const Boid& boid) {
    std::vector<Boid> neighbours;

    for (const auto candidate : boids_) {
        double current_dist = boid.getDistance(candidate);
        if (current_dist < boid.neighbourhood_radius) {
            neighbours.emplace_back(candidate);
        }
    }

    // Need to check for this since we the current boids will also have
    // the boid under comparison, as such the neighbours will always
    // have atleast 1 member
    if (neighbours.size() > 1) return neighbours;

    return std::vector<Boid>{};
}

}  // namespace boids