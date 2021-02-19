#include "Visualization.h"
#include "PathFinding.h"

namespace pathfinding {

const uint32_t Visualizer::m_sleep_duration_ms = 0.01 * microseconds_in_seconds;

Visualizer::Visualizer(const PathFinder* path_finder) {
    cell_size_ = path_finder->getEnvironment()->getCellSize();
    width_ = cell_size_ * path_finder->getEnvironment()->getCols() + 1;
    height_ = cell_size_ * path_finder->getEnvironment()->getRows() + 1;
    path_ = path_finder->getPath();
    env_type_ = path_finder->getEnvironmentType();
    env_ = path_finder->getEnvironment();
}

void Visualizer::setTitle(const char* title) { title_ = title; }

void Visualizer::setTheme(const Theme& theme) { theme_ = theme; }

void Visualizer::show() {
    switch (env_type_) {
        case EnvironmentType::GRID:
            showGrid();
            break;
        case EnvironmentType::MAZE:
            showMaze();
            break;
        default:
            LOG(FATAL) << "Unknown environment type for path finding!";
            break;
    }
}

void Visualizer::showGrid() {
    // TODO: Add check for checking if path was
    // calculated
    SDL_bool quit = SDL_FALSE;

    // A variable to keep track of
    // how many waypoints we are showing
    // This is to aid progression of path
    int num_path_waypoints = 1;

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

        // Iterate through the path and fill up rectangles with
        // path color
        // TODO: Make it progressional
        SDL_SetRenderDrawColor(renderer_, path_color_.r, path_color_.g,
                               path_color_.b, path_color_.a);

        for (int i = 0; i < num_path_waypoints; ++i) {
            auto cell = *path_[i];

            // Form the rectangle to be rendered
            SDL_Rect rect;
            rect.x = cell.getCol() * cell_size_;
            rect.y = cell.getRow() * cell_size_;
            rect.w = cell_size_;
            rect.h = cell_size_;

            // Fill the rectangle
            SDL_RenderFillRect(renderer_, &rect);
        }

        num_path_waypoints = (num_path_waypoints < path_.size())
                                 ? num_path_waypoints + 1
                                 : num_path_waypoints;

        SDL_SetRenderDrawColor(renderer_, grid_line_color_.r,
                               grid_line_color_.g, grid_line_color_.b,
                               grid_line_color_.a);

        // Draw horizontal grid lines
        for (int row = 0; row < width_; row += cell_size_) {
            SDL_RenderDrawLine(renderer_, row, 0, row, height_ - 1);
        }
        // Draw vertical grid lines
        for (int col = 0; col < height_; col += cell_size_) {
            SDL_RenderDrawLine(renderer_, 0, col, width_ - 1, col);
        }

        // Present the render
        SDL_RenderPresent(renderer_);

        // Sleep
        usleep(m_sleep_duration_ms);
    }

    // Destroy
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Visualizer::showMaze() {
    SDL_bool quit = SDL_FALSE;

    // To track the number of current waypoints shown
    // Helps in showing path progression
    int num_path_waypoints = 1;

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

        // TODO: Check if width and height have been set

        // Iterate through the path and fill up the rectangles with path
        // color
        SDL_SetRenderDrawColor(renderer_, path_color_.r, path_color_.g,
                               path_color_.b, path_color_.a);

        // Add waypoints progressionally
        for (int i = 0; i < num_path_waypoints; ++i) {
            auto cell = *path_[i];

            // Form the rectangle to be rendered
            SDL_Rect rect;
            rect.x = cell.getCol() * cell_size_;
            rect.y = cell.getRow() * cell_size_;
            rect.w = cell_size_;
            rect.h = cell_size_;

            // Fill the rectangle
            SDL_RenderFillRect(renderer_, &rect);
        }

        num_path_waypoints = (num_path_waypoints < path_.size())
                                 ? num_path_waypoints + 1
                                 : num_path_waypoints;

        // Show the maze walls
        // TODO: move me to another function (although cleverly since
        // we cant have maze and grid functions defined all over the place)
        // Major GOTCHA! getWalls is not virtual and hence its not callable
        // Easy fix would be just create a virtual getWalls inside environment
        // Later to be replaced by a getParams which can then be utilized as
        // we see fit.
        SDL_SetRenderDrawColor(renderer_, grid_line_color_.r,
                               grid_line_color_.g, grid_line_color_.b,
                               grid_line_color_.a);

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

        // Additionally add walls denoting maze outerboundaries
        SDL_RenderDrawLine(renderer_, 0, 0, width_ - 1, 0);
        SDL_RenderDrawLine(renderer_, 0, 0, 0, height_ - 1);
        SDL_RenderDrawLine(renderer_, 0, height_ - 1, width_ - 1, height_ - 1);
        SDL_RenderDrawLine(renderer_, width_ - 1, height_ - 1, width_ - 1, 0);

        // Present the render
        SDL_RenderPresent(renderer_);

        // Sleep
        usleep(m_sleep_duration_ms);
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
    background_color_ = {65, 60, 48, 255};    // color code #413C30
    grid_line_color_ = {223, 222, 221, 255};  // color code #DFDEDD
    path_color_ = {255, 31, 31, 255};         // some version of blue // FIX ME
    traversal_cell_color_ = {123, 163, 219,
                             255};           // some version of green // FIXE ME
    waypoint_color_ = {137, 225, 117, 255};  // some version of red // FIX ME
}

void Visualizer::setLightTheme() {
    background_color_ = {223, 222, 221, 255};  // color code #DFDEDD
    grid_line_color_ = {223, 222, 221, 255};   // color code #DFDEDD
    path_color_ = {255, 31, 31, 255};          // some version of blue // FIX ME
    traversal_cell_color_ = {123, 163, 219,
                             255};           // some version of green // FIX ME
    waypoint_color_ = {137, 225, 117, 255};  // some version of red // FIX ME
}

}  // namespace pathfinding