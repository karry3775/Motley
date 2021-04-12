#include <simple_pendulum.h>

namespace pendulum {

SimplePendulum::SimplePendulum() {
    // TODO
}

SimplePendulum::SimplePendulum(const double length, const double radius,
                               const double ini_theta)
    : length_(length), radius_(radius), theta_(ini_theta), time_(0) {}

void SimplePendulum::show() {
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

        // Update pendulum
        update(interval);

        // render buffer
        viz_.renderCurrentBuffer();

        // box blur
        viz_.boxBlur();
    }
}

void SimplePendulum::update(const int interval) {
    // theta = theta_ini * cos( sqrt(g / l) * interval)

    // TODO
}

}  // namespace pendulum