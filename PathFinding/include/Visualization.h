#pragma once

#include <SDL2/SDL.h>
#include "Grid.h"

namespace pathfinding {

class Visualizer {
   public:
    enum Theme { DARK, LIGHT };

    Visualizer();
    ~Visualizer();

    /**
     * Function to set the window title
     */
    void setTitle(const char*);

    /**
     * Function to set the fig size
     * from width and height
     */
    void setSize(const uint32_t&, const uint32_t&);

    /**
     * Function to set the theme of the visualizer
     */
    void setTheme(const Theme&);

    /**
     *  Shows the environment visualization
     * @param Grid Grid type object
     */
    void showEnvironment(const Grid&);

    /**
     * Shows the path in the evironment
     * Assumes that the environment exists
     * to visualizer a path in.
     * @param Path Path type object
     */
    void showPath(const Path<Cell>&);

   private:
    bool init();
    void setLightTheme();
    void setDarkTheme();

    uint32_t width_;
    uint32_t height_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Color background_color_;
    SDL_Color grid_line_color_;
    SDL_Color traversal_cell_color_;
    SDL_Color path_color_;
    SDL_Color waypoint_color_;

    Theme theme_;
    const char* title_;
};

}  // namespace pathfinding
