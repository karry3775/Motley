#pragma once

#include <SDL2/SDL.h>
#include "Grid.h"
#include "EnvironmentGeneration.h"
#include <unistd.h>  // TODO: Switch to boost for portability

#define microseconds_in_seconds 1000000

namespace pathfinding {

class PathFinder;  // Forward declaration

enum class Theme { DARK, LIGHT };

class Visualizer {
   public:
    Visualizer();

    Visualizer(const PathFinder*);

    ~Visualizer() = default;

    /**
     * Function to set the window title
     */
    void setTitle(const char*);

    /**
     * Function to set the theme of the visualizer
     */
    void setTheme(const Theme&);

    /**
     * Set path
     */
    void setPath(const Path<Cell*>& path);

    /**
     * Initiate the visualizer
     */
    bool init();

    /**
     * Set path
     */
    void setPath(const Path<Cell*>* path);

    /**
     *  Shows the visualization
     */
    void showFinalPath();

    /**
     * Show Path progression
     */
    void showPathProgression(const Path<Cell*>& path);

    // The functions below should become private later on

    /**
     * Visualizer pathfinding for Grid environment
     */
    void showPathGrid(const Path<Cell*>& path, const bool is_progression);

    /**
     * Visualize pathfinding for maze environment
     */
    void showPathMaze(const Path<Cell*>& path, const bool is_progression);

   private:
    void setLightTheme();
    void setDarkTheme();
    void renderBackground();
    void renderPath(const Path<Cell*>& path, const uint32_t& num_waypoints,
                    const bool is_progression);
    void renderWalls();
    void renderCell(const Cell& cell, const SDL_Color& color);
    void renderBoundaries();
    void renderGridLines();
    void renderWayPoints(const Path<Cell*>& path,
                         const uint32_t& num_waypoints);
    void renderWayPointPair(const Cell& c1, const Cell& c2);
    void renderCircle(int x0, int y0);

    void renderObstacles();

    uint32_t width_;
    uint32_t height_;
    uint32_t cell_size_;
    uint32_t waypoint_radius_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Color start_color_;
    SDL_Color end_color_;
    SDL_Color background_color_;
    SDL_Color grid_line_color_;
    SDL_Color traversal_cell_color_;
    SDL_Color path_color_;
    SDL_Color waypoint_line_color_;
    SDL_Color waypoint_circle_color_;
    SDL_Color obstacles_color_;

    Theme theme_;
    const char* title_;

    Path<Cell*> path_;

    Cell start_;

    Cell end_;

    std::vector<std::vector<int>> obstacles_;

    bool path_exists_;

    // Environment
    const Environment<Cell>* env_;

    // Environment type
    EnvironmentType env_type_;

    // sleep duration in milliseconds
    static const uint32_t m_sleep_duration_ms;
};

}  // namespace pathfinding
