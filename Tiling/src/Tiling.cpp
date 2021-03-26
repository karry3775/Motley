#include <Tiling.h>

namespace tiling {

Tiler::Tiler(const uint32_t N, const uint32_t cell_size)
    : N_(N), cell_size_(cell_size) {
    initViz();
}

void Tiler::visualize(const TilingSequences& all_ts) {
    int all_ts_idx = 0;
    int tile_idx = 0;
    SDL_bool quit = SDL_FALSE;

    while (!quit && all_ts_idx < all_ts.size()) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
                break;
            }
        }

        // Draw grid background
        SDL_SetRenderDrawColor(renderer_, bg_color.r, bg_color.g, bg_color.b,
                               bg_color.a);
        SDL_RenderClear(renderer_);

        SDL_SetRenderDrawColor(renderer_, placed_tile_color.r,
                               placed_tile_color.g, placed_tile_color.b,
                               placed_tile_color.a);
        // Render placed tiles (less than current index)
        renderPlacedTiles(all_ts[all_ts_idx], tile_idx);

        SDL_SetRenderDrawColor(renderer_, current_tile_color.r,
                               current_tile_color.g, current_tile_color.b,
                               current_tile_color.a);
        // Render current tile
        renderTile(all_ts[all_ts_idx][tile_idx]);

        // Draw grid lines
        SDL_SetRenderDrawColor(renderer_, line_color.r, line_color.g,
                               line_color.b, line_color.a);

        for (int x = 0; x < 1 + grid_width_ * cell_size_; x += cell_size_) {
            SDL_RenderDrawLine(renderer_, x, 0, x, window_height_);
        }

        for (int y = 0; y < 1 + grid_height_ * cell_size_; y += cell_size_) {
            SDL_RenderDrawLine(renderer_, 0, y, window_width_, y);
        }

        // Present render
        SDL_RenderPresent(renderer_);

        if (tile_idx == all_ts[all_ts_idx].size() - 1) {
            // Reset
            tile_idx = 0;
            // Increment ts_idx
            all_ts_idx++;
        } else {
            tile_idx++;
        }

        usleep(kSleepDurationMs);
    }  // end of game loop

    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Tiler::getAllTilings(TilingSequences& all_ts) {
    TilingSequence ts;
    getAllTilings(0, true, true, ts, all_ts);
}

void Tiler::getAllTilings(const uint32_t col, const bool t1, const bool t2,
                          TilingSequence ts, TilingSequences& all_ts) {
    // Base case
    if (col == N_ - 1) {
        if (t1 && t2) {
            ts.emplace_back(getDominoVertical(col));
            all_ts.emplace_back(ts);
        } else if (!t1 && !t2) {
            all_ts.emplace_back(ts);
        }

        return;
    }

    // Cases to explore
    // Other wise we have a lot of cases to explore
    if (t1 && t2) {
        // Case 1:
        // XO
        // XO
        ts.emplace_back(getDominoVertical(col));
        // Recurse
        getAllTilings(col + 1, true, true, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // XX
        // XO
        ts.emplace_back(getTrominoTopLeft(col));
        // Recurse
        getAllTilings(col + 1, false, true, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 3:
        // XO
        // XX
        ts.emplace_back(getTrominoBottomLeft(col));
        // Recurse
        getAllTilings(col + 1, true, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 4:
        // X X
        // Y Y
        ts.emplace_back(getDominoHorizontal(0, col));
        ts.emplace_back(getDominoHorizontal(1, col));
        // Recurse
        getAllTilings(col + 1, false, false, ts, all_ts);
        // Backtrack
        ts.pop_back();
        ts.pop_back();

    } else if (t1) {
        // t1 is free t2 is blocked

        // Case 1:
        // X X
        // # X
        ts.emplace_back(getTrominoTopRight(col));
        // Recurse
        getAllTilings(col + 1, false, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // X X
        // #
        ts.emplace_back(getDominoHorizontal(0, col));
        // Recurse
        getAllTilings(col + 1, false, true, ts, all_ts);
        // Back track
        ts.pop_back();
    } else if (t2) {
        // t1 is blocked t2 is free

        // Case 1:
        // # X
        // X X
        ts.emplace_back(getTrominoBottomRight(col));
        // Recurse
        getAllTilings(col + 1, false, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // #
        // X X
        ts.emplace_back(getDominoHorizontal(1, col));
        // Recurse
        getAllTilings(col + 1, true, false, ts, all_ts);
        // Backtrack
        ts.pop_back();
    } else {
        // Both are blocked

        // We just move forward
        getAllTilings(col + 1, true, true, ts, all_ts);
    }
}

void Tiler::initViz() {
    // Define grid params
    grid_width_ = N_;
    grid_height_ = 2;

    // + 1 for window params so that last grid lines fit in
    // the screen
    window_width_ = (grid_width_ * cell_size_) + 1;
    window_height_ = (grid_height_ * cell_size_) + 1;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return;
    }

    // Create window and renderer
    if (SDL_CreateWindowAndRenderer(window_width_, window_height_, 0, &window_,
                                    &renderer_) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer %s", SDL_GetError());
        return;
    }

    // Set window title
    SDL_SetWindowTitle(window_, kWindowTitle);
}

//
// Domino Generators
//

// X
// X
Tile Tiler::getDominoVertical(const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));
    return t;
}
// X X
Tile Tiler::getDominoHorizontal(const uint32_t row, const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(row, col));
    t.emplace_back(std::make_pair(row, col + 1));
    return t;
}

//
// Tromino Generators
//

// X X
// X
Tile Tiler::getTrominoTopLeft(const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(0, col + 1));
    return t;
}

// X
// X X
Tile Tiler::getTrominoBottomLeft(const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(1, col + 1));
    return t;
}

// X X
//   X
Tile Tiler::getTrominoTopRight(const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(0, col + 1));
    t.emplace_back(std::make_pair(1, col + 1));
    return t;
}

//   X
// X X
Tile Tiler::getTrominoBottomRight(const uint32_t col) {
    Tile t;
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(1, col + 1));
    t.emplace_back(std::make_pair(0, col + 1));
    return t;
}

//
// Visualization functions
//
void Tiler::renderTile(const Tile& tile) {
    for (auto cell : tile) {
        SDL_Rect rect = {cell.second * cell_size_, cell.first * cell_size_,
                         cell_size_, cell_size_};

        SDL_RenderFillRect(renderer_, &rect);
    }
}

void Tiler::renderPlacedTiles(const TilingSequence& ts, int tile_idx) {
    for (int i = 0; i < tile_idx; ++i) {
        renderTile(ts[i]);
    }
}

}  // namespace tiling
