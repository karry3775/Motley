#include <Defaults.h>

namespace ant_colony {

// TODO: Verify if this is best way to initialize static members
// Think production quality code ?

/*----------------------- SDL Colors ------------------------------*/

// Barley black
const SDL_Color Defaults::bg_color = {22, 22, 22, 255};
// Hex #52B8B8
const SDL_Color Defaults::nest_color = {82, 184, 184, 255};
// Hex #CFDADA
const SDL_Color Defaults::ant_foraging_color = {207, 218, 218, 255};
const SDL_Color Defaults::ant_returning_color = {0, 255, 20, 255};

// Hex #B3BFFF
const SDL_Color Defaults::forage_color{255, 0, 0};

/*----------------------- SDL Window params -----------------------*/

const uint32_t Defaults::window_width = 750;   // px
const uint32_t Defaults::window_height = 750;  // px

const char* Defaults::window_title = "Ant Colony Simulation";

/*-------------------- Render Properties --------------------------*/

const uint32_t Defaults::sleep_duration_ms = 0.01 * kMicrosecondsInASecond;

/*------------------------ Nest Params ----------------------------*/
const double Defaults::nest_radius = 10;  // px
const Position Defaults::nest_pos =
    Position(Defaults::window_width / 2, Defaults::window_height / 2);

/*------------------------- Randomization Params ------------------*/
const double Defaults::max_angle_window = (10 * M_PI / 180);

/*-----------------------Forage size-------------------------------*/
const uint32_t Defaults::forage_size = 4;
const double Defaults::forage_radius = 10;
const double Defaults::food_salvation_thresh = 5;

}  // namespace ant_colony