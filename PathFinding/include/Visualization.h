#pragma once

#include <SDL2/SDL.h>
#include "Grid.h"
#include "PathFinding.h"
#include <unistd.h>  // TODO: Switch to boost for portability

#define microseconds_in_seconds 1000000

namespace pathfinding {

enum class Theme { DARK, LIGHT };

class Visualizer {
   public:
    Visualizer();

    Visualizer(const PathFinder*);

    ~Visualizer();

    /**
     * Function to set the window title
     */
    void setTitle(const char*);

    /**
     * Function to set the theme of the visualizer
     */
    void setTheme(const Theme&);

    /**
     * Initiate the visualizer
     */
    bool init();

    /**
     *  Shows the visualization
     */
    void show();

   private:
    void setLightTheme();
    void setDarkTheme();

    uint32_t width_;
    uint32_t height_;
    uint32_t cell_size_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Color background_color_;
    SDL_Color grid_line_color_;
    SDL_Color traversal_cell_color_;
    SDL_Color path_color_;
    SDL_Color waypoint_color_;

    Theme theme_;
    const char* title_;

    Path<Cell*> path_;

    // sleep duration in milliseconds
    static const uint32_t m_sleep_duration_ms;
};

}  // namespace pathfinding
