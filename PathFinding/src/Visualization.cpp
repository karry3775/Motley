#include "Visualization.h"
#include "PathFinding.h"

DEFINE_int32(waypoint_radius, 3, "radius for a waypoint renderer through SDL");

namespace pathfinding {

const uint32_t Visualizer::m_sleep_duration_ms =
    0.001 * microseconds_in_seconds;

Visualizer::Visualizer(const PathFinder* path_finder) {
    cell_size_ = path_finder->getEnvironment()->getCellSize();
    width_ = cell_size_ * path_finder->getEnvironment()->getCols() + 1;
    height_ = cell_size_ * path_finder->getEnvironment()->getRows() + 1;
    path_ = path_finder->getPath();
    start_ = path_finder->getStartCell();
    end_ = path_finder->getEndCell();
    env_type_ = path_finder->getEnvironmentType();
    env_ = path_finder->getEnvironment();
    waypoint_radius_ = FLAGS_waypoint_radius;
    path_exists_ = path_finder->doesPathExists();

    CHECK_NE(width_, 0);
    CHECK_NE(height_, 0);
    CHECK_NE(cell_size_, 0);

    switch (env_type_) {
        case EnvironmentType::GRID:
            obstacles_ = path_finder->getObstacles();
            break;
        case EnvironmentType::MAZE:
            // For specifying maze specific properties for
            // visualizer in future
            break;
        default:
            // Although this will be first caught by the path finder
            LOG(FATAL) << "Unknown environment type!";
            break;
    }
}

void Visualizer::setTitle(const char* title) { title_ = title; }

void Visualizer::setTheme(const Theme& theme) { theme_ = theme; }

void Visualizer::setPath(const Path<Cell*>& path) { path_ = path; }

void Visualizer::showFinalPath() {
    switch (env_type_) {
        case EnvironmentType::GRID:
            showPathGrid(path_, false);
            break;
        case EnvironmentType::MAZE:
            showPathMaze(path_, false);
            break;
        default:
            LOG(FATAL) << "Unknown environment type for path finding!";
            break;
    }
}

void Visualizer::showPathProgression(const Path<Cell*>& path) {
    switch (env_type_) {
        case EnvironmentType::GRID:
            showPathGrid(path, true);
            break;
        case EnvironmentType::MAZE:
            showPathMaze(path, true);
            break;
        default:
            LOG(FATAL) << "Unknonw environment type for path finding!";
    }
}

void Visualizer::showPathGrid(const Path<Cell*>& path,
                              const bool is_progression) {
    SDL_bool quit = SDL_FALSE;

    // A variable to keep track of
    // how many waypoints we are showing
    // This is to aid progression of path

    // if we are showing the final path then we do not need any progression
    // and thus number of path waypoints to be rendered can be
    // just set to full path size.
    int num_current_path_waypoints = (is_progression) ? 1 : path.size();

    // Only used when is_progression is true
    // If not a progression then num_current_path_waypoint suffices
    int num_final_path_waypoints_when_progression = 1;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }
        // Render background
        renderBackground();

        // Render obstacles
        renderObstacles();

        // Render Path
        renderPath(path, num_current_path_waypoints, is_progression);

        if (is_progression && num_current_path_waypoints == path.size()) {
            // Also render the final path once the explored path is finished
            renderPath(path_, num_final_path_waypoints_when_progression, false);
            // Update num_final_path_waypoints
            num_final_path_waypoints_when_progression =
                (num_final_path_waypoints_when_progression < path_.size())
                    ? num_final_path_waypoints_when_progression + 1
                    : num_final_path_waypoints_when_progression;
        }

        // Render grid lines
        renderGridLines();

        if (!is_progression) {
            // Render Waypoints
            renderWayPoints(path, num_current_path_waypoints);
        }

        if (is_progression && num_current_path_waypoints == path.size()) {
            renderWayPoints(path_, num_final_path_waypoints_when_progression);
        }

        // Present the render
        SDL_RenderPresent(renderer_);

        // Sleep
        usleep(m_sleep_duration_ms);

        // Update number of way points to be displayed
        num_current_path_waypoints = (num_current_path_waypoints < path.size())
                                         ? num_current_path_waypoints + 1
                                         : num_current_path_waypoints;
    }

    // Destroy
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Visualizer::showPathMaze(const Path<Cell*>& path,
                              const bool is_progression) {
    // TODO: Check if width and height have been set
    SDL_bool quit = SDL_FALSE;

    // if we are showing the final path then we do not need any progression
    // and thus number of path waypoints to be rendered can be
    // just set to full path size.
    int num_current_path_waypoints = (is_progression) ? 1 : path.size();

    // Only used when is_progression is true
    // If not a progression then num_current_path_waypoint suffices
    int num_final_path_waypoints_when_progression = 1;

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }

        // Render background
        renderBackground();

        // Render Path
        renderPath(path, num_current_path_waypoints, is_progression);

        if (is_progression && num_current_path_waypoints == path.size()) {
            // Also render the final path once the explored path is finished
            renderPath(path_, num_final_path_waypoints_when_progression, false);
            // Update num_final_path_waypoints
            num_final_path_waypoints_when_progression =
                (num_final_path_waypoints_when_progression < path_.size())
                    ? num_final_path_waypoints_when_progression + 1
                    : num_final_path_waypoints_when_progression;
        }

        // Render walls
        renderWalls();

        // render outer boundaries
        renderBoundaries();

        if (!is_progression) {
            // Render Waypoints
            renderWayPoints(path, num_current_path_waypoints);
        }

        if (is_progression && num_current_path_waypoints == path.size()) {
            renderWayPoints(path_, num_final_path_waypoints_when_progression);
        }

        // Present the render
        SDL_RenderPresent(renderer_);

        // Sleep
        usleep(m_sleep_duration_ms);

        // Update number of way points to be displayed
        num_current_path_waypoints = (num_current_path_waypoints < path.size())
                                         ? num_current_path_waypoints + 1
                                         : num_current_path_waypoints;
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

// good source to set colors: https://www.w3schools.com/css/css_colors_rgb.asp
void Visualizer::setDarkTheme() {
    start_color_ = {60, 179, 113, 255};
    end_color_ = {255, 99, 71, 255};
    background_color_ = {65, 60, 48, 255};
    grid_line_color_ = {223, 222, 221, 255};
    path_color_ = {106, 90, 205, 255};
    traversal_cell_color_ = {255, 68, 217, 100};
    waypoint_line_color_ = {137, 225, 117, 255};
    waypoint_circle_color_ = {177, 137, 51, 255};
    obstacles_color_ = {180, 180, 180, 255};
}

void Visualizer::setLightTheme() {
    start_color_ = {60, 179, 113, 255};
    end_color_ = {255, 99, 71, 255};
    background_color_ = {223, 222, 221, 255};
    grid_line_color_ = {65, 60, 48, 255};
    path_color_ = {106, 90, 205, 255};
    traversal_cell_color_ = {255, 68, 217, 100};
    waypoint_line_color_ = {137, 225, 117, 255};
    waypoint_circle_color_ = {177, 137, 51, 255};
    obstacles_color_ = {60, 60, 60, 255};
}

void Visualizer::renderBackground() {
    SDL_SetRenderDrawColor(renderer_, background_color_.r, background_color_.g,
                           background_color_.b, background_color_.a);
    SDL_RenderClear(renderer_);
}

void Visualizer::renderPath(const Path<Cell*>& path,
                            const uint32_t& num_waypoints,
                            const bool is_progression) {
    CHECK_NE(path.size(), 0) << "renderPath: Received an empty path!";
    SDL_Color path_color =
        (is_progression) ? traversal_cell_color_ : path_color_;
    // Add waypoints progressionally
    for (int i = 0; i < num_waypoints; ++i) {
        auto cell = *path[i];

        // Form the rectangle to be rendered
        renderCell(cell, path_color);
    }
    // Render start cell
    renderCell(start_, start_color_);

    // Render end cell
    renderCell(end_, end_color_);
}

void Visualizer::renderWalls() {
    // Major GOTCHA! getWalls was not virtual and hence its not callable unless
    // made one Easy fix would be just create a virtual getWalls inside
    // environment Later to be replaced by a virtual getParams which can then be
    // utilized as we see fit.

    // Set render color
    SDL_SetRenderDrawColor(renderer_, grid_line_color_.r, grid_line_color_.g,
                           grid_line_color_.b, grid_line_color_.a);

    // Render walls
    for (auto& wall_ptr : env_->getWalls()) {
        CHECK(wall_ptr->getItems().size() != 0) << "walls are empty!";

        // Get the corners for the walls
        std::vector<uint32_t> corners;

        std::set<Corner> items = wall_ptr->getItems();
        for (auto itr = items.begin(); itr != items.end(); ++itr) {
            corners.push_back(itr->getCol());
            corners.push_back(itr->getRow());
        }

        // Draw the line
        SDL_RenderDrawLine(renderer_, corners[0], corners[1], corners[2],
                           corners[3]);
    }
}

void Visualizer::renderCell(const Cell& cell, const SDL_Color& color) {
    // Set render color
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

    // Create the cell rectangle to be rendered
    SDL_Rect rect;
    rect.x = cell.getCol() * cell_size_;
    rect.y = cell.getRow() * cell_size_;
    rect.w = cell_size_;
    rect.h = cell_size_;

    // Push to the renderer
    SDL_RenderFillRect(renderer_, &rect);
}

void Visualizer::renderBoundaries() {
    SDL_RenderDrawLine(renderer_, 0, 0, width_ - 1, 0);
    SDL_RenderDrawLine(renderer_, 0, 0, 0, height_ - 1);
    SDL_RenderDrawLine(renderer_, 0, height_ - 1, width_ - 1, height_ - 1);
    SDL_RenderDrawLine(renderer_, width_ - 1, height_ - 1, width_ - 1, 0);
}

void Visualizer::renderGridLines() {
    SDL_SetRenderDrawColor(renderer_, grid_line_color_.r, grid_line_color_.g,
                           grid_line_color_.b, grid_line_color_.a);

    // Draw horizontal grid lines
    for (int row = 0; row < width_; row += cell_size_) {
        SDL_RenderDrawLine(renderer_, row, 0, row, height_ - 1);
    }
    // Draw vertical grid lines
    for (int col = 0; col < height_; col += cell_size_) {
        SDL_RenderDrawLine(renderer_, 0, col, width_ - 1, col);
    }
}

void Visualizer::renderWayPoints(const Path<Cell*>& path,
                                 const uint32_t& num_waypoints) {
    // Add waypoints progressionally
    for (int i = 0; i < num_waypoints - 1; ++i) {
        auto cell1 = *path[i];
        auto cell2 = *path[i + 1];

        // Render waypoint pair
        renderWayPointPair(cell1, cell2);
    }
}

void Visualizer::renderWayPointPair(const Cell& c1, const Cell& c2) {
    CHECK(cell_size_ % 2 == 0) << "cell_size needs to be even";
    SDL_SetRenderDrawColor(renderer_, waypoint_line_color_.r,
                           waypoint_line_color_.g, waypoint_line_color_.b,
                           waypoint_line_color_.a);

    if (path_exists_) {
        // Draw line joining the two lines
        SDL_RenderDrawLine(renderer_,
                           (c1.getCol() * cell_size_) + cell_size_ / 2,
                           (c1.getRow() * cell_size_) + cell_size_ / 2,
                           (c2.getCol() * cell_size_) + cell_size_ / 2,
                           (c2.getRow() * cell_size_) + cell_size_ / 2);
    }

    SDL_SetRenderDrawColor(renderer_, waypoint_circle_color_.r,
                           waypoint_line_color_.g, waypoint_line_color_.b,
                           waypoint_line_color_.a);

    // Draw end points
    renderCircle(c1.getCol() * cell_size_ + cell_size_ / 2,
                 c1.getRow() * cell_size_ + cell_size_ / 2);
    renderCircle(c2.getCol() * cell_size_ + cell_size_ / 2,
                 c2.getRow() * cell_size_ + cell_size_ / 2);
}

void Visualizer::renderCircle(int x0, int y0) {
    // Source : https://gist.github.com/henkman/1b6f4492b82dc76adad1dc110c923baa
    int x = waypoint_radius_;
    int y = 0;
    int radius_error = 1 - x;

    while (x >= y) {
        SDL_RenderDrawLine(renderer_, x + x0, y + y0, -x + x0, y + y0);
        SDL_RenderDrawLine(renderer_, y + x0, x + y0, -y + x0, x + y0);
        SDL_RenderDrawLine(renderer_, -x + x0, -y + y0, x + x0, -y + y0);
        SDL_RenderDrawLine(renderer_, -y + x0, -x + y0, y + x0, -x + y0);
        y++;
        if (radius_error < 0)
            radius_error += 2 * y + 1;
        else {
            x--;
            radius_error += 2 * (y - x + 1);
        }
    }
}

void Visualizer::renderObstacles() {
    CHECK(!obstacles_.empty()) << "No obstacles specified. Was this intended!";

    // Iterate through all the obstacles and render them
    for (int i = 0; i < obstacles_.size(); ++i) {
        for (int j = 0; j < obstacles_[0].size(); ++j) {
            if (obstacles_[i][j] == 1) renderCell(Cell(i, j), obstacles_color_);
        }
    }
}

}  // namespace pathfinding