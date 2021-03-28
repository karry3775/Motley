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
const SDL_Color Defaults::ant_color = {207, 218, 218, 255};
// Hex #B3BFFF
const SDL_Color Defaults::food_color = {179, 191, 255, 100};

/*----------------------- SDL Window params -----------------------*/

const uint32_t Defaults::window_width = 500;   // px
const uint32_t Defaults::window_height = 500;  // px

const char* Defaults::window_title = "Ant Colony Simulation";

/*-------------------- Render Properties --------------------------*/

const uint32_t Defaults::sleep_duration_ms = 0.01 * kMicrosecondsInASecond;

/*------------------------ Nest Params ----------------------------*/
const uint32_t Defaults::nest_radius = 50;  // px
const Position Defaults::nest_pos =
    Position(Defaults::window_width / 2, Defaults::window_height / 2);

/*------------------------- Randomization Params ------------------*/
const double Defaults::max_angle_window = (10 * M_PI / 180);

}  // namespace ant_colony