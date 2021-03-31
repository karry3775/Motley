#pragma once

#include <Core.h>

namespace boids {

struct Viz {
    Viz();

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

    // Viz properties
    SDL_Color boid_color;
    uint32_t width;
    uint32_t height;
    char* title;    
};  // Viz

}  // namespace boids