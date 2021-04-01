#include <Boids.h>
#include <iostream>

namespace boids {

const double Boids::coh_wt = 0;
const double Boids::sep_wt = 1;
const double Boids::ali_wt = 0;

const double Boids::max_vel = 0.1;

constexpr double turnfactor = 1;

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
        Uint8 red = 10 + Uint8(abs(255 * red_factor));
        Uint8 green = 10 + Uint8(abs(255 * green_factor));
        Uint8 blue = 10 + Uint8(abs(255 * blue_factor));

        // viz_.setPixelColor(boid.x, boid.y, red, green, blue);

        for (int x = -2; x < 2; ++x) {
            for (int y = -2; y < 2; ++y) {
                if (x * x + y * y <= 2 * 2) {
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

        std::cout << "separation: " << separation.x << ", " << separation.y
                  << "\n";

        // Rule 2: Alignment --  Set the heading to be equal to average
        // heading of the neighbour hood
        auto alignment = getAlignmentVector(boid, neighbours);

        std::cout << "separation: " << alignment.x << ", " << alignment.y
                  << "\n";

        // Rule 3: Cohesion -- Steer to move towards average location of the
        // neighbour
        auto cohesion = getCohesionVector(boid, neighbours);

        std::cout << "separation: " << cohesion.x << ", " << cohesion.y << "\n";

        // Form a final acceleration
        auto acceleration =
            separation * sep_wt + cohesion * coh_wt + alignment * ali_wt;

        auto random_v = Vector(getRandWithin(-6, 6), getRandWithin(-6, 6));

        acceleration += random_v;

        std::cout << "acceleration : " << acceleration.x << ", "
                  << acceleration.y << "\n";

        // Update velocity
        boid.vel += acceleration * interval;

        boid.vel.x = std::min(max_vel, boid.vel.x);
        boid.vel.y = std::min(max_vel, boid.vel.y);

        // Update position
        boid.pos += boid.vel * interval;

        if(boid.pos.x < 0) {
            boid.pos.x += turnfactor;
        }
        if(boid.pos.x > viz_.width) {
            boid.pos.x -= turnfactor;
        }
        if(boid.pos.y < 0) {
            boid.pos.y += turnfactor;
        }
        if(boid.pos.y > viz_.height) {
            boid.pos.y -= turnfactor;
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
    sep.normalize();

    return sep;
}

Vector Boids::getAlignmentVector(const Boid& boid,
                                 const std::vector<Boid>& neighbours) {
    Vector ali;

    // Return zero vector if no neighbours
    if (neighbours.empty()) return ali;

    for (const auto& ngh : neighbours) {
        ali += ngh.pos;
    }

    // Normalize
    ali.normalize();

    return ali;
}

Vector Boids::getCohesionVector(const Boid& boid,
                                const std::vector<Boid>& neighbours) {
    Vector coh;

    // Return zero vector if no neighbours
    if (neighbours.empty()) return coh;

    for (const auto& ngh : neighbours) {
        Vector outwards =
            Vector(ngh.pos.x - boid.pos.x, ngh.pos.y - boid.pos.y);
        coh += outwards;
    }

    // Normalize
    coh.normalize();

    return coh;
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