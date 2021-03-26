#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <unistd.h>

constexpr const uint32_t kMicrosecondsInASecond = 1000000;
constexpr const uint32_t kSleepDurationMs = 0.11 * kMicrosecondsInASecond;
constexpr const char* kWindowTitle = "Domino Tromino Tiling";

namespace tiling {

typedef std::vector<std::pair<uint32_t, uint32_t>> Tile;
typedef std::vector<Tile> TilingSequence;
typedef std::vector<TilingSequence> TilingSequences;

class Tiler {
   public:
    Tiler(const uint32_t N, const uint32_t cell_size);
    void getAllTilings(TilingSequences& all_ts);
    void visualize(const TilingSequences& all_ts);

   private:
    // Overloaded Helper function for getAllTilings
    void getAllTilings(const uint32_t col, const bool t1, const bool t2,
                       TilingSequence ts, TilingSequences& all_ts);
    // Viz init
    void initViz();

    // Domino generators
    Tile getDominoVertical(const uint32_t col);
    Tile getDominoHorizontal(const uint32_t row, const uint32_t col);

    // Tromino generators
    Tile getTrominoTopLeft(const uint32_t col);
    Tile getTrominoBottomLeft(const uint32_t col);
    Tile getTrominoTopRight(const uint32_t col);
    Tile getTrominoBottomRight(const uint32_t col);

    // Visualization Functions
    void renderTile(const Tile& tile);
    void renderPlacedTiles(const TilingSequence& ts, int tile_idx);

    // Tile properties
    uint32_t N_;

    // Colors
    SDL_Color bg_color = {22, 22, 22, 255};             // Barley black
    SDL_Color line_color = {255, 255, 255, 255};        // White color
    SDL_Color placed_tile_color = {0, 0, 255, 255};     // Blue color
    SDL_Color current_tile_color = {255, 255, 0, 255};  // Yellow color

    // SDL objects
    SDL_Window* window_;
    SDL_Renderer* renderer_;

    // Render properties
    const uint32_t cell_size_;
    uint32_t grid_width_;
    uint32_t grid_height_;
    uint32_t window_width_;
    uint32_t window_height_;
};

}  // namespace tiling