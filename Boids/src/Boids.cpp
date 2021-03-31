#include <Boids.h>

namespace boids {

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
        boid.x = (double(rand()) / RAND_MAX) * viz_.width;
        boid.y = (double(rand()) / RAND_MAX) * viz_.height;
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
        viz_.setPixelColor(boid.x, boid.y, viz_.boid_color.r, viz_.boid_color.g,
                           viz_.boid_color.b);
    }
}

}  // namespace boids