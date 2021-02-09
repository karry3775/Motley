#include "Visualization.h"
#include "PathFinding.h"

namespace pathfinding {

Visualizer::Visualizer(const PathFinder* path_finder) {
    cell_size_ = path_finder->getGrid()->getCellSize();
    width_ = cell_size_ * path_finder->getGrid()->getCols() + 1;
    height_ = cell_size_ * path_finder->getGrid()->getRows() + 1;
}

void Visualizer::setTitle(const char* title) { title_ = title; }

void Visualizer::setTheme(const Theme& theme) { theme_ = theme; }

void Visualizer::showEnvironment() {
    SDL_bool quit = SDL_FALSE;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }
        // Render background
        SDL_SetRenderDrawColor(renderer_, background_color_.r,
                               background_color_.g, background_color_.b,
                               background_color_.a);
        SDL_RenderClear(renderer_);

        // TODO: Add a check to see if the width_ and
        // height_ have been set

        SDL_SetRenderDrawColor(renderer_, grid_line_color_.r,
                               grid_line_color_.g, grid_line_color_.b,
                               grid_line_color_.a);

        // Draw horizontal grid lines
        for (int row = 0; row < width_; row += cell_size_) {
            SDL_RenderDrawLine(renderer_, row, 0, row, height_);
        }
        // Draw vertical grid lines
        for (int col = 0; col < height_; col += cell_size_) {
            SDL_RenderDrawLine(renderer_, 0, col, width_, col);
        }

        // Present the render
        SDL_RenderPresent(renderer_);
    }

    // Destroy
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

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
        case Theme::DARK:
            setDarkTheme();
            break;
        case Theme::LIGHT:
            setLightTheme();
            break;
        default:
            setDarkTheme();
            break;
    }

    return true;
}

void Visualizer::setDarkTheme() {
    background_color_ = {65, 60, 48, 255};         // color code #413C30
    grid_line_color_ = {223, 222, 221, 255};       // color code #DFDEDD
    traversal_cell_color_ = {123, 163, 219, 255};  // some version of blue
    path_color_ = {137, 225, 117, 255};            // some version of green
    waypoint_color_ = {255, 31, 31, 255};          // some version of red
}

void Visualizer::setLightTheme() {
    background_color_ = {223, 222, 221, 255};      // color code #DFDEDD
    grid_line_color_ = {65, 60, 48, 255};          // color code #413C30
    traversal_cell_color_ = {123, 163, 219, 255};  // Bleu de France
    path_color_ = {137, 225, 117, 255};            // some version of green
    waypoint_color_ = {255, 31, 31, 255};          // some version of red
}

}  // namespace pathfinding