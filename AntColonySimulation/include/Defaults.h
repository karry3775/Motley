#pragma once

#include <Core.h>

namespace ant_colony {

// NOTE: Since this is more about the visualization,
// we do not want the end user to worry about setting things
// from the constructor as that clutters the usage
// We want to set just SDL properties by default, which is extactly
// the function of this struct

struct Defaults {
    // SDL Color
    static const SDL_Color bg_color;
    static const SDL_Color nest_color;
    static const SDL_Color ant_foraging_color;
    static const SDL_Color ant_returning_color;
    static const SDL_Color forage_color;

    // SDL Window params
    static const uint32_t window_width;
    static const uint32_t window_height;
    static const char* window_title;

    // Render properties
    static const uint32_t sleep_duration_ms;

    // Nest Params
    static const double nest_radius;
    static const Position nest_pos;

    // Randomization Parms
    static const double max_angle_window;

    // Forage Params
    static const uint32_t forage_size;
    static const double forage_radius;
    static const double food_salvation_thresh;
};

}  // namespace ant_colony