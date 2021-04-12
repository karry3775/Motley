#pragma once

#include "core.h"

namespace pendulum {

struct Visualizer {
    Visualizer();

    void init();
    void destroy();
    void setPixelColor(int posx, int posy, Uint8 red, Uint8 green, Uint8 blue);
    void boxBlur();
    void renderCurrentBuffer();

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    Uint32* buffer;
    Uint32* blur_buffer;

    SDL_Color rod_color;
    uint32_t width;
    uint32_t height;
    char* title;
};  // Visualizer

}  // namespace pendulum