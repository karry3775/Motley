#include "Visualization.h"

namespace pathfinding {

void Visualizer::setTitle(const char* title) { title_ = title; }

void Visualizer::setSize(const uint32_t& width, const uint32_t& height) {
    width_ = width;
    height_ = height;
}

void Visualizer::setTheme(const Theme& theme) { theme_ = theme; }

bool Visualizer::init() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return false;
    }

    // Create window and renderer
    if (SDL_CreateWindowAndRenderer(width_, height_, 0, &window_, &renderer_) <
        0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return false;
    }

    // Set the window title
    SDL_SetWindowTitle(window_, title_);

    // Set colors according to the theme
    switch (theme_) {
        case DARK:
            setDarkTheme();
            break;
        case LIGHT:
            setLightTheme();
            break;
        default:
            setDarkTheme();
            break;
    }

    return true;
}

void Visualizer::setDarkTheme() {
    // TODO
    background_color_ = {65, 60, 48, 255};        // color code #413C30
    grid_line_color_ = {223, 222, 221, 255};      // color code #DFDEDD
    traversal_cell_color_ = {49, 140, 231, 255};  // some version of blue
    path_color_ = {};                             // some version of green
    waypoint_color_ = {};                         // some version of red
}

void Visualizer::setLightTheme() {
    // TODO
    background_color_ = {223, 222, 221, 255};     // color code #DFDEDD
    grid_line_color_ = {65, 60, 48, 255};         // color code #413C30
    traversal_cell_color_ = {49, 140, 231, 255};  // Bleu de France
    path_color_ = {};                             // some version of green
    waypoint_color_ = {};                         // some version of red
}

}  // namespace pathfinding