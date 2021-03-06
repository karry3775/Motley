#include <Defaults.h>

namespace ant_colony {

// TODO: Verify if this is best way to initialize static members
// Think production quality code ?

/*----------------------- SDL Colors ------------------------------*/

// Barley black
const SDL_Color Defaults::bg_color = {22, 22, 22, 255};
// Hex #52B8B8
const SDL_Color Defaults::nest_color = {194, 163, 122, 255};
// Hex #CFDADA
const SDL_Color Defaults::trail_seek_color = {102, 179, 255, 255};
const SDL_Color Defaults::trail_return_color = {255, 38, 51, 255};
const SDL_Color Defaults::ant_color = {255, 230, 179, 255};

// Hex #B3BFFF
const SDL_Color Defaults::forage_color{173, 230, 230, 255};

/*----------------------- SDL Window params -----------------------*/

const uint32_t Defaults::window_width = 900;   // 750;   // px
const uint32_t Defaults::window_height = 900;  // 750;  // px

const char* Defaults::window_title = "Ant Colony Simulation";

/*-------------------- Render Properties --------------------------*/

const uint32_t Defaults::sleep_duration_ms = 0.01 * kMicrosecondsInASecond;

/*------------------------ Nest Params ----------------------------*/
const double Defaults::nest_radius = 10;  // px
const Position Defaults::nest_pos =
    Position(Defaults::window_width / 2, Defaults::window_height / 2);

/*------------------------- Randomization Params ------------------*/
const double Defaults::max_angle_window = (50 * M_PI / 180);

/*-----------------------Forage size-------------------------------*/
const uint32_t Defaults::forage_size = 8;
const double Defaults::forage_radius = 5 /*10*/;
const double Defaults::food_salvation_thresh = 5;

/*--------------------- Pheromone strength -----------------------*/
const uint32_t Defaults::pheromone_strength = 500;
const uint32_t Defaults::decay_rate = 2;

}  // namespace ant_colony