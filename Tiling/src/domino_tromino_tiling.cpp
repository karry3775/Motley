#include <SDL2/SDL.h>
#include <vector>
#include <unistd.h>
#include <iostream>

#define microseconds_in_second 1000000

typedef std::vector<std::pair<int, int>> Tile;
typedef std::vector<Tile> TilingSequence;
typedef std::vector<TilingSequence> TilingSequences;

const uint32_t sleep_duration_ms = 0.11 * microseconds_in_second;

SDL_Color bg_color = {22, 22, 22, 255};             // Barley black
SDL_Color line_color = {255, 255, 255, 255};        // White color
SDL_Color placed_tile_color = {0, 0, 255, 255};     // Blue color
SDL_Color current_tile_color = {255, 255, 0, 255};  // Yellow color

int cell_size = 200;

SDL_Window* window;
SDL_Renderer* renderer;

// X
// X
Tile getVerticalDomino(int col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));

    return t;
}

// X X
Tile getHorizontalDomino(int row, int col) {
    Tile t;
    t.emplace_back(std::make_pair(row, col));
    t.emplace_back(std::make_pair(row, col + 1));

    return t;
}

// X X
// X
Tile getTrominoTopLeft(int col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(0, col + 1));

    return t;
}

// X
// X X
Tile getTrominoBottomLeft(int col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(1, col + 1));

    return t;
}

// X X
//   X
Tile getTrominoTopRight(int col) {
    Tile t;
    t.emplace_back(std::make_pair(0, col));
    t.emplace_back(std::make_pair(0, col + 1));
    t.emplace_back(std::make_pair(1, col + 1));

    return t;
}

//   X
// X X
Tile getTrominoBottomRight(int col) {
    Tile t;
    t.emplace_back(std::make_pair(1, col));
    t.emplace_back(std::make_pair(1, col + 1));
    t.emplace_back(std::make_pair(0, col + 1));
    return t;
}

void getAllTilings(int col, int N, bool t1, bool t2, TilingSequence ts,
                   TilingSequences& all_ts) {
    if (col == N - 1) {
        if (t1 && t2) {
            ts.emplace_back(getVerticalDomino(col));
            all_ts.emplace_back(ts);
        } else if (!t1 && !t2) {
            all_ts.emplace_back(ts);
        }
        return;
    }

    // Other wise we have a lot of cases to explore
    if (t1 && t2) {
        // Case 1:
        // XO
        // XO
        ts.emplace_back(getVerticalDomino(col));
        // Recurse
        getAllTilings(col + 1, N, true, true, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // XX
        // XO
        ts.emplace_back(getTrominoTopLeft(col));
        // Recurse
        getAllTilings(col + 1, N, false, true, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 3:
        // XO
        // XX
        ts.emplace_back(getTrominoBottomLeft(col));
        // Recurse
        getAllTilings(col + 1, N, true, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 4:
        // X X
        // Y Y
        ts.emplace_back(getHorizontalDomino(0, col));
        ts.emplace_back(getHorizontalDomino(1, col));
        // Recurse
        getAllTilings(col + 1, N, false, false, ts, all_ts);
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
        getAllTilings(col + 1, N, false, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // X X
        // #
        ts.emplace_back(getHorizontalDomino(0, col));
        // Recurse
        getAllTilings(col + 1, N, false, true, ts, all_ts);
        // Back track
        ts.pop_back();
    } else if (t2) {
        // t1 is blocked t2 is free

        // Case 1:
        // # X
        // X X
        ts.emplace_back(getTrominoBottomRight(col));
        // Recurse
        getAllTilings(col + 1, N, false, false, ts, all_ts);
        // Backtrack
        ts.pop_back();

        // Case 2:
        // #
        // X X
        ts.emplace_back(getHorizontalDomino(1, col));
        // Recurse
        getAllTilings(col + 1, N, true, false, ts, all_ts);
        // Backtrack
        ts.pop_back();
    } else {
        // Both are blocked

        // We just move forward
        getAllTilings(col + 1, N, true, true, ts, all_ts);
    }
}

void getAllTilings(int N, TilingSequences& all_ts) {
    TilingSequence ts;
    getAllTilings(0, N, true, true, ts, all_ts);
}

void renderTile(const Tile& tile) {
    for (auto cell : tile) {
        SDL_Rect rect = {cell.second * cell_size, cell.first * cell_size,
                         cell_size, cell_size};

        SDL_RenderFillRect(renderer, &rect);
    }
}

void renderPlacedTiles(const TilingSequence& ts, int tile_idx) {
    for (int i = 0; i < tile_idx; ++i) {
        renderTile(ts[i]);
    }
}

int main() {
    /*---------------- Code to get all tiling configurations ------------ */
    int N = 5;
    TilingSequences all_ts;
    getAllTilings(N, all_ts);

    std::cerr << "Found " << all_ts.size() << " sequences!\n";

    /* ------------------------------------------------------------------- */
    int grid_width = N;
    int grid_height = 2;

    // +1 so that last grid lines fit in the screen
    int window_width = (grid_width * cell_size) + 1;
    int window_height = (grid_height * cell_size) + 1;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
                                    &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "Domino-Tromino Tiling");

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
        SDL_SetRenderDrawColor(renderer, bg_color.r, bg_color.g, bg_color.b,
                               bg_color.a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, placed_tile_color.r,
                               placed_tile_color.g, placed_tile_color.b,
                               placed_tile_color.a);
        // Render placed tiles (less than current index)
        renderPlacedTiles(all_ts[all_ts_idx], tile_idx);

        SDL_SetRenderDrawColor(renderer, current_tile_color.r,
                               current_tile_color.g, current_tile_color.b,
                               current_tile_color.a);
        // Render current tile
        renderTile(all_ts[all_ts_idx][tile_idx]);

        // Draw grid lines
        SDL_SetRenderDrawColor(renderer, line_color.r, line_color.g,
                               line_color.b, line_color.a);

        for (int x = 0; x < 1 + grid_width * cell_size; x += cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        for (int y = 0; y < 1 + grid_height * cell_size; y += cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }

        // Present render
        SDL_RenderPresent(renderer);

        if (tile_idx == all_ts[all_ts_idx].size() - 1) {
            // Reset
            tile_idx = 0;
            // Increment ts_idx
            all_ts_idx++;
        } else {
            tile_idx++;
        }

        usleep(sleep_duration_ms);
    }  // end of game loop

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cerr << "Finished!\n";

    return EXIT_SUCCESS;
}